/****************************************************************************
 
 Copyright (c) 2017-2020 Kevin Wu (Wu Feng)
 
 github: http://github.com/kevinwu1024
 
 Licensed under the MIT License (the "License"); you may not use this file except
 in compliance with the License. You may obtain a copy of the License at
 
 http://opensource.org/licenses/MIT
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NON INFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 
 ****************************************************************************/

#include "SCMemAllocator.h"
#include <memory>
#include <mutex>

NAMESPACE_SPEEDCC_BEGIN

#ifdef SPEEDCC_FEATURE_MEMORY_POOL_THREAD_SAFE
    static std::mutex* s_pLock = nullptr;
#endif
    
char* SCPoolAllocator::_pFreeStart = 0;
char* SCPoolAllocator::_pFreeEnd = 0;
size_t SCPoolAllocator::_nHeapSize = 0;
    
SCPoolAllocator::SCMemBlock* SCPoolAllocator ::_pFreeList[SCPoolAllocator::NUMBER_OF_FREE_LIST] = {0};
    
    
char* SCPoolAllocator::allocChunk(size_t nSize,int& nNodeNumber)
{
    char* pRet = 0;
    size_t nTotalBytes = nSize * nNodeNumber;
    size_t nLeftBytes = _pFreeEnd - _pFreeStart;
        
    if(nLeftBytes >= nTotalBytes)
    {
        pRet = _pFreeStart;
        _pFreeStart += nTotalBytes;
            
        return pRet;
    }
    else if(nLeftBytes >= nSize)
    {
        nNodeNumber = (int)(nLeftBytes/nSize);
        nTotalBytes = nSize * nNodeNumber;
        pRet = _pFreeStart;
        _pFreeStart += nTotalBytes;
            
        return pRet;
    }
    else
    {
        size_t nSizeOfGet = 2 * nTotalBytes + SCPoolAllocator::roundUp(_nHeapSize >> 4);
            
        if(nLeftBytes > 0)
        {
            SCMemBlock* * pFreeList = _pFreeList + SCPoolAllocator::getIndexInFreeList(nLeftBytes);
                
            ((SCMemBlock*)_pFreeStart)->pNext = *pFreeList;
            *pFreeList = (SCMemBlock*)_pFreeStart;
        }
            
        _pFreeStart = (char*)malloc(nSizeOfGet);
            
        if(0 == _pFreeStart)
        {
            SCMemBlock** pFreeList;
            SCMemBlock* pTem;
                
            for (size_t i = nSize; i <= (size_t) SIZE_OF_MAX_IN_BYTES; i += (size_t) SIZE_OF_ALIGN)
            {
                pFreeList = _pFreeList + SCPoolAllocator::getIndexInFreeList(i);
                pTem = *pFreeList;
                    
                if(0 != pTem)
                {
                    *pFreeList = pTem -> pNext;
                    _pFreeStart = (char*)pTem;
                    _pFreeEnd = _pFreeStart + i;
                        
                    return SCPoolAllocator::allocChunk(nSize, nNodeNumber);
                }
            }
                
            _pFreeEnd = 0;
            _pFreeStart = (char*)malloc(nSizeOfGet);
        }
            
        _nHeapSize += nSizeOfGet;
        _pFreeEnd = _pFreeStart + nSizeOfGet;
            
        return SCPoolAllocator::allocChunk(nSize, nNodeNumber);
    }
}
    
void* SCPoolAllocator::refill(size_t nSize)
{
    int nNodeNumber = 20;
    char* pChunk = SCPoolAllocator::allocChunk(nSize, nNodeNumber);
    SCMemBlock** pFreeList = 0;
    SCMemBlock* pRet = 0;
    SCMemBlock* pCurrentNode = 0;
    SCMemBlock* pNode = 0;
        
    if(1 == nNodeNumber)
    {
        return pChunk;
    }
        
    pFreeList = _pFreeList + SCPoolAllocator::getIndexInFreeList(nSize);
        
    // build free list in chunk
    pRet = (SCMemBlock*)pChunk;
    *pFreeList = pNode = (SCMemBlock*)(pChunk + nSize);
        
    for (int i = 1;; i++)
    {
        pCurrentNode = pNode;
        pNode = (SCMemBlock*)((char*)pNode + nSize);
            
        if(nNodeNumber - 1 == i)
        {
            pCurrentNode->pNext = 0;
            break;
        }
        else
        {
            pCurrentNode->pNext = pNode;
        }
    }
        
    return pRet;
}
    
    
void* SCPoolAllocator::allocate(size_t nSize)
{
#ifdef SPEEDCC_FEATURE_MEMORY_POOL_THREAD_SAFE
    if(s_pLock==nullptr)
    {
        s_pLock = new std::mutex();
    }
    SCAutoLock(*s_pLock);
#endif
    SCASSERT(nSize>0);
        
    void* pRet = 0;
        
    if(nSize > (size_t) SIZE_OF_MAX_IN_BYTES)
    {
        pRet = ::malloc(nSize);
    }
    else
    {
        SCMemBlock** pFreeList = _pFreeList + SCPoolAllocator::getIndexInFreeList(nSize);
            
        SCMemBlock*  pResult = *pFreeList;
            
        if(pResult == 0)
        {
            pRet = SCPoolAllocator::refill(SCPoolAllocator::roundUp(nSize));
        }
        else
        {
            *pFreeList = pResult -> pNext;
            pRet = pResult;
        }
    }
        
    //SCLog("SCPoolAllocator::allocate() address=%p size=%d",pRet,nSize);
        
    return pRet;
}
    
void SCPoolAllocator::deallocate(void* pBuffer, size_t nSize)
{
#ifdef SPEEDCC_FEATURE_MEMORY_POOL_THREAD_SAFE
    if(s_pLock==nullptr)
    {
        s_pLock = new std::mutex();
    }
    SCAutoLock(*s_pLock);
#endif
        
    SCASSERT(pBuffer!=0);
    SCASSERT(nSize>0);
        
    //SCLog("SCPoolAllocator::deallocate() address=%p size=%d",pBuffer,nSize);
        
    if(nSize > (size_t) SIZE_OF_MAX_IN_BYTES)
    {
        ::free(pBuffer);
    }
    else
    {
        SCMemBlock**  pFreeList = _pFreeList + SCPoolAllocator::getIndexInFreeList(nSize);
        SCMemBlock* pTem = (SCMemBlock*)pBuffer;
            
        pTem -> pNext = *pFreeList;
        *pFreeList = pTem;
    }
}

NAMESPACE_SPEEDCC_END

