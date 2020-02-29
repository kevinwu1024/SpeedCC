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

package org.speedcc.lib;

import android.content.Intent;
import android.util.Log;

import org.speedcc.lib.iap.IabHelper;
import org.speedcc.lib.iap.IabResult;
import org.speedcc.lib.iap.Inventory;
import org.speedcc.lib.iap.Purchase;
import org.speedcc.lib.iap.SkuDetails;

import java.util.ArrayList;
import java.util.List;


public class GooglePlayIAP {

    private static String TAG = "GooglePlayBilling";
    // (arbitrary) request code for the purchase flow
    static final int RC_REQUEST = 10001;

    private IabHelper mHelper;

    // Called when consumption is complete
    IabHelper.OnConsumeFinishedListener mConsumeFinishedListener = new IabHelper.OnConsumeFinishedListener() {
        public void onConsumeFinished(Purchase purchase, IabResult result) {
            Log.d(TAG, "Consumption finished. Purchase: " + purchase + ", result: " + result);

            // if we were disposed of in the meantime, quit.
            if (mHelper == null) return;
        }
    };

    public GooglePlayIAP(){
        Log.d(TAG, "Creating IAB helper.");
        String base64EncodedPublicKey = "";
        mHelper = new IabHelper(SpeedCCActivity.getActivity(), base64EncodedPublicKey);

        mHelper.enableDebugLogging(true);

        mHelper.startSetup(new IabHelper.OnIabSetupFinishedListener() {
            public void onIabSetupFinished(IabResult result) {

                if(result.isFailure()){
                    Log.d(TAG, "IAB Setup failed.");
                }else{
                    Log.d(TAG, "IAB Setup failed.");
                }
                Log.d(TAG, "IAB Setup successful.");
            }
        });
    }

    public void purchaseItem(String sku, boolean isConsumable) {

        Log.d(TAG, "purchaseItem v3 " + sku);
        final String finalSku = sku;
        final boolean finalIsConsumable = isConsumable;
        SpeedCCActivity.getActivity().runOnUiThread(new Runnable() {
            public void run() {
                IabHelper.OnIabPurchaseFinishedListener purchaseFinishedListener = new IabHelper.OnIabPurchaseFinishedListener() {
                    public void onIabPurchaseFinished(IabResult result, Purchase purchase) {
                        Log.d(TAG, "Purchase finished: " + result + ", purchase: " + purchase);

                        // if we were disposed of in the meantime, quit.

                        if (mHelper == null){
                            onPurchaseResultEvent(finalSku,1);
                            return;
                        }

                        if (finalIsConsumable) {
                            Log.d(TAG, "Purchase is consumable");
                            if ( purchase != null ) {
                                try{
                                    mHelper.consumeAsync(purchase, mConsumeFinishedListener);
                                }catch(IabHelper.IabAsyncInProgressException e){

                                }
                            }
                        }

                        if (result.isFailure()) {
                            Log.d(TAG,"Error purchasing: " + result);
                            onPurchaseResultEvent(finalSku,1);
                            return;
                        }

                        Log.d(TAG, "Purchase successful.");
                        onPurchaseResultEvent(finalSku,0);

                    }
                };
                Log.d(TAG,"purchaseItem()");

                String payload = "";

                try{
                    mHelper.launchPurchaseFlow(SpeedCCActivity.getActivity(), finalSku, RC_REQUEST,
                            purchaseFinishedListener, payload);
                }catch(IabHelper.IabAsyncInProgressException e){

                }
            }
        });

    }

    public void restoreItem() {
        Log.d(TAG, "restoreTransactions ");
        SpeedCCActivity.getActivity().runOnUiThread(new Runnable() {
            public void run() {
                try{
                    mHelper.queryInventoryAsync(new IabHelper.QueryInventoryFinishedListener() {
                        public void onQueryInventoryFinished(IabResult result, Inventory inventory) {
                            Log.d(TAG, "Query inventory finished.");

                            // Have we been disposed of in the meantime? If so, quit.
                            if (mHelper == null) return;

                            // Is it a failure?
                            if (result == null || result.isFailure()) {
                                Log.d(TAG,"Failed to query inventory: " + result);
                                return;
                            }

                            Log.d(TAG, "Query inventory was successful.");
                            Log.d(TAG,result.toString());

                        }
                    });
                }catch(IabHelper.IabAsyncInProgressException e){

                }

            }
        });
    }

    public void requestItemPrice(String sku){
        // restoreTransactions();
        Log.d(TAG, "requestItemPrice : " + sku);
        if(mHelper==null){
            return;
        }

        Log.d(TAG, "requestItemPrice2 : " + sku);
        final String finalSku = sku;
        Log.d(TAG, "requestItemPrice3 : " + sku);
        SpeedCCActivity.getActivity().runOnUiThread(new Runnable() {
            public void run() {
                List<String> skuList = new ArrayList<String>();
                skuList.add(finalSku);
                List<String> subskuList = new ArrayList<String>();
                try{
                    mHelper.queryInventoryAsync( true, skuList,subskuList, new IabHelper.QueryInventoryFinishedListener() {
                        public void onQueryInventoryFinished(IabResult result, Inventory inventory) {
                            Log.d(TAG, "Query inventory finished.");

                            // Have we been disposed of in the meantime? If so, quit.
                            if (mHelper == null) return;

                            // Is it a failure?
                            if (result == null || result.isFailure()) {
                                Log.d(TAG,"Failed to query inventory: " + result);
                                return;
                            }

                            Log.d(TAG, "Query inventory was successful.");
                            Log.d(TAG,result.toString());
			            /*
			             * Check for items we own. Notice that for each purchase, we check
			             * the developer payload to see if it's correct! See
			             * verifyDeveloperPayload().
			             */
                            Log.d(TAG, "sku:"+ finalSku );

                            if ( inventory != null ) {

                                if(inventory.getPurchase(finalSku)!=null){
                                    Log.d(TAG,"Get Purchase Success!");
                                }else{
                                    Log.d(TAG,"Get Purchase Failed!");
                                }

                                if(inventory.hasDetails(finalSku)){
                                    SkuDetails detail = inventory.getSkuDetails(finalSku);
                                    Log.d(TAG, "sku:"+ finalSku );
                                    //Log.d(TAG, "sku:"+ sku + " price:"+detail.getPrice());
                                    onPurchaseItemPriceEvent(finalSku,detail.getPriceCurrencyCode(), Float.parseFloat(detail.getPrice()));
                                }
                            }
                        }
                    });
                }catch(IabHelper.IabAsyncInProgressException e){

                }

            }
        });
    }

    public boolean handleActivityResult(int requestCode, int resultCode, Intent data) {

        Log.d(TAG, "handleActivityResult : " + requestCode );
        if(mHelper==null){
            return false;
        }
        return mHelper.handleActivityResult(requestCode, resultCode, data);
    }

    private static native int onPurchaseResultEvent(String sku,int result);
    private static native int onPurchaseItemPriceEvent(String sku,String currency,float price);

}
