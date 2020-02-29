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

#ifndef __SPEEDCC__SCBUFFERQUEUE_H__
#define __SPEEDCC__SCBUFFERQUEUE_H__


#include <memory.h> 
#include <assert.h>
#include <mutex>

namespace SpeedCC
{
    template<bool bSafe_>
    class SCThreadLocker
    {
    public:
        SCThreadLocker() {}
        ~SCThreadLocker() {}
        inline void lock() const {}
        inline void unlock() const {}
    };
    
    
    template<>
    class SCThreadLocker<true>
    {
    public:
        SCThreadLocker() {}
        ~SCThreadLocker() {}
        inline void lock() { _locker.lock();};
        inline void unlock() { _locker.unlock();};
        
    private:
        std::mutex  _locker;
    };
    
    ///------------- SCCircleQueueT
    template<bool bThreadSafe_,unsigned nBufSize_=128>
    class SCBufferQueueT
    {
    public:
        SCBufferQueueT()
        {
            _pBuffer = (char*)::malloc(nBufSize_);
            assert(_pBuffer!=nullptr);
            
            this->cleanUp();
        }
        
        virtual ~SCBufferQueueT()
        {
            if(_pBuffer!=nullptr)
            {
                ::free(_pBuffer);
                _pBuffer = nullptr;
            }
        }
        
        unsigned getLength()
        {
            unsigned uResult;
            
            _locker.lock();
            uResult = this->getLengthNoLock();
            _locker.unlock();
            
            return uResult;
        }
        
        void cleanUp()
        {
            _locker.lock();
            
            _nHeadPos = -1;  // tail position doesn't include element
            _nTailPos = -1;  // head position doesn't include element
            _overflowBufVtr.clear();
            
            _locker.unlock();
        }
        
        
        bool isEmpty()
        {
            bool bResult;
            
            _locker.lock();
            bResult = this->isEmptyNoLock();
            _locker.unlock();
            
            return bResult;
        }
        
        unsigned getBufferSize() const
        {
            return nBufSize_;
        }
        
        int popFront(char* pDest,unsigned uLen)
        {
            if(pDest==nullptr || uLen==0 || this->isEmpty())
            {
                return 0;
            }
            
            _locker.lock();
            
            auto uBlockUsedSize = this->getBlockLengthNoLock();
            unsigned uActualLen = std::min(uLen,uBlockUsedSize);
            
            if(_nHeadPos+uActualLen > nBufSize_-1)
            {// copy in 2 pieces
                int nFrontLen = nBufSize_ - _nHeadPos -1;
                int nBackLen = uActualLen - nFrontLen;
                
                ::memcpy(pDest,_pBuffer+_nHeadPos+1,nFrontLen);
                ::memcpy(pDest+nFrontLen,_pBuffer,nBackLen);
                
                _nHeadPos = nBackLen-1;
            }
            else
            {
                ::memcpy(pDest,_pBuffer+_nHeadPos+1,uActualLen);
                _nHeadPos += uActualLen;
            }
            
            if(uLen > uActualLen && !_overflowBufVtr.empty())
            {// if pop buffer size has more room, copy overflow buffer to it
                auto uRemainLen = uLen - uActualLen;
                auto uActualLen2 = std::min(uRemainLen,(unsigned)_overflowBufVtr.size());
                ::memcpy(pDest+uActualLen,_overflowBufVtr.data(),uActualLen2);
                _overflowBufVtr.erase(_overflowBufVtr.begin(), _overflowBufVtr.begin() + uActualLen2);
                
                uActualLen += uActualLen2;
            }
            
            if(_nHeadPos==_nTailPos)
            {// there is no element when head reach tail
                _nHeadPos = -1;
                _nTailPos = -1;
            }
            
            this->moveOverflow2BlockNoLock();
            
            _locker.unlock();
            
            return uActualLen;
        }
        
        void pushBack(const char* pSource,unsigned nLen)
        {
            _locker.lock();
            auto uFreeSize = nBufSize_ - this->getBlockLengthNoLock();
            if(uFreeSize < nLen)
            {
                if(uFreeSize>0)
                {
                    assert(_overflowBufVtr.empty());
                    this->pushBlockBackNoLock(pSource,uFreeSize);
                }
                _overflowBufVtr.insert(_overflowBufVtr.end(), pSource + (uFreeSize * sizeof(char)), pSource + (nLen * sizeof(char)));
            }
            else
            {
                this->pushBlockBackNoLock(pSource,nLen);
            }
            _locker.unlock();
        }
        
    private:
        bool isEmptyNoLock()
        {
            return (_nHeadPos==-1 && _nTailPos==-1) && _overflowBufVtr.empty();
        }
        
        unsigned getLengthNoLock()
        {
            return this->getBlockLengthNoLock() + (unsigned)_overflowBufVtr.size();
        }
        
        unsigned getBlockLengthNoLock()
        {
            if(_nHeadPos==-1 && _nTailPos==-1)
            {
                return 0;
            }
            else
            {
                if(_nTailPos==_nHeadPos && _nTailPos!=-1)
                {
                    return nBufSize_;
                }
                else
                {
                    return (_nTailPos - _nHeadPos + (_nTailPos>=_nHeadPos ? 0 : nBufSize_));
                }
            }
        }
        
        void pushBlockBackNoLock(const char* pSource,unsigned nLen)
        {
            if(_nTailPos+(int)nLen>(int)nBufSize_-1)
            {// copy in 2 pieces
                int nFrontLen = nBufSize_-_nTailPos-1;
                int nBackLen = nLen - nFrontLen;
                ::memcpy(_pBuffer+_nTailPos+1,pSource,nFrontLen);
                ::memcpy(_pBuffer,pSource+nFrontLen,nBackLen);
                
                _nTailPos = nBackLen-1;
            }
            else
            {
                ::memcpy(_pBuffer+_nTailPos+1,pSource,nLen);
                _nTailPos += nLen;
            }
        }
        
        void moveOverflow2BlockNoLock()
        {
            if(!_overflowBufVtr.empty())
            {
                auto uMinSize = std::min(nBufSize_ - this->getBlockLengthNoLock(),(unsigned)_overflowBufVtr.size());
                if(uMinSize>0)
                {
                    this->pushBlockBackNoLock(_overflowBufVtr.data(),uMinSize);
                    _overflowBufVtr.erase(_overflowBufVtr.begin(), _overflowBufVtr.begin() + uMinSize);
                }
            }
        }
        
    private:
        int                 _nTailPos;       // tail position, tail position doesn't include element
        int                 _nHeadPos;       // head position, head position doesn't include element
        char*               _pBuffer;        // pointer to buffer of queue
        std::vector<char>   _overflowBufVtr;
        
        SCThreadLocker<bThreadSafe_>    _locker;
    };
}



#endif // __SPEEDCC__SCBUFFERQUEUE_H__
