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


import android.app.AlertDialog;
import android.app.Dialog;
import android.app.UiModeManager;
import android.content.DialogInterface;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.content.res.Configuration;

import org.cocos2dx.lib.Cocos2dxActivity;

import java.text.DateFormatSymbols;

import static android.content.Context.UI_MODE_SERVICE;

public class JNISystem {

    public static int getOrientation(){
        switch(Cocos2dxActivity.getContext().getResources().getConfiguration().orientation)
        {
            case Configuration.ORIENTATION_LANDSCAPE: return 3;
            case Configuration.ORIENTATION_PORTRAIT: return 1;
            default: return 0;
        }
    }

    public static String getMonthName(int month,boolean isShort){

        DateFormatSymbols dfs = new DateFormatSymbols();
        String[] months = isShort ? dfs.getShortMonths() : dfs.getMonths();

        String ret = "";
        if(month>0 && month<13){
            ret = months[month-1];
        }
        return ret;
    }

    public static String getWeekName(int week,boolean isShort){

        DateFormatSymbols dfs = new DateFormatSymbols();
        String[] weeks = isShort ? dfs.getShortWeekdays() : dfs.getWeekdays();

        String ret = "";
        if(week>0 && week<8){
            ret = weeks[week];
        }
        return ret;
    }


    public static String getPackageName(){

        return Cocos2dxActivity.getContext().getPackageName();
    }

    public static String getProductName(){
        PackageManager packageManager = Cocos2dxActivity.getContext().getPackageManager();
        ApplicationInfo applicationInfo = null;
        try {
            applicationInfo = packageManager.getApplicationInfo(Cocos2dxActivity.getContext().getApplicationInfo().packageName, 0);
        } catch (final PackageManager.NameNotFoundException e) {
        }
        return (String) (applicationInfo != null ? packageManager.getApplicationLabel(applicationInfo) : "Unknown");
    }

    public static String getAppVersion(){
        try{
            PackageInfo pInfo = Cocos2dxActivity.getContext().getPackageManager().getPackageInfo(Cocos2dxActivity.getContext().getPackageName(), 0);
            return pInfo.versionName;
        }
        catch(Exception e){
            return "";
        }
    }


    // device type. 0: unkown; 1: phone; 2: tablet; 3: tv; 4:vehicle; 5: desktop
    public static int getDeviceType(){
        int nRet = 0;
        UiModeManager uiModeManager = (UiModeManager) Cocos2dxActivity.getContext().getSystemService(UI_MODE_SERVICE);
        if (uiModeManager.getCurrentModeType() == Configuration.UI_MODE_TYPE_TELEVISION) {
            nRet = 3;
        }else {
            boolean xlarge = ((Cocos2dxActivity.getContext().getResources().getConfiguration().screenLayout & Configuration.SCREENLAYOUT_SIZE_MASK) == 4);
            boolean large = ((Cocos2dxActivity.getContext().getResources().getConfiguration().screenLayout & Configuration.SCREENLAYOUT_SIZE_MASK) == Configuration.SCREENLAYOUT_SIZE_LARGE);
            nRet = (xlarge || large) ? 2 : 1;
        }
        return nRet;
    }

    public static String getDeviceModel(){
        return android.os.Build.MODEL;
    }

    public static String getDeviceManufacturer(){
        return android.os.Build.MANUFACTURER;
    }

    public static String getDeviceBrand(){
        return android.os.Build.BRAND;
    }

    public static String getDeviceProduct(){
        return android.os.Build.PRODUCT;
    }

    public static String getOSVersion(){
        return android.os.Build.VERSION.RELEASE;
    }

    public static String getSDCardWritablePath(){
        File file = Cocos2dxActivity.getContext().getExternalFilesDir(null);
        if (null != file) {
            return file.getPath();
        }

        return Cocos2dxActivity.getContext().getFilesDir().getAbsolutePath();
    }

    public static void installAPK(String strAPKFile){
        if (strAPKFile.equals("")) {
            return;
        }

        File apkFile = new File(strAPKFile);
        if (null == apkFile || !apkFile.exists()) {
            return;
        }

        Intent installIntent = new Intent(Intent.ACTION_VIEW);
        installIntent.setDataAndType(Uri.fromFile(apkFile), "application/vnd.android.package-archive");
        instance.startActivity(installIntent);
    }

    public static void setMultipleTouch(boolean isEnabled)
    {
        ((Cocos2dxActivity)(Cocos2dxActivity.getContext())).getGLSurfaceView().setMultipleTouchEnabled(isEnabled);
    }

    public static boolean getMultipleTouch()
    {
        return ((Cocos2dxActivity)(Cocos2dxActivity.getContext())).getGLSurfaceView().isMultipleTouchEnabled();
    }

    public static void showMessageBox(final String title, final String message,
                                      final String button1, final String button2, final String button3,
                                      final int messageID)
    {


        final AlertDialog.Builder alertDialogBuilder = new AlertDialog.Builder(Cocos2dxActivity.getContext());

        // set title
        alertDialogBuilder.setTitle(title);

        // set dialog message
        alertDialogBuilder
                .setMessage(message)
                .setCancelable(true);

        if ( button1 != null && !"".equals(button1) ) {
            alertDialogBuilder.setNegativeButton(button1, new DialogInterface.OnClickListener() {
                public void onClick(DialogInterface dialog,int id) {

                    onAlertBoxSelected( 0,messageID );
                    dialog.dismiss();
                }
            });
        }

        if ( button2 != null && !"".equals(button2) ) {
            alertDialogBuilder.setPositiveButton(button2, new DialogInterface.OnClickListener() {
                public void onClick(DialogInterface dialog,int id) {

                    onAlertBoxSelected( 1,messageID);
                    dialog.cancel();
                }
            });
        }
        if ( button3 != null && !"".equals(button3) ) {
            alertDialogBuilder.setNeutralButton(button3, new DialogInterface.OnClickListener() {
                public void onClick(DialogInterface dialog,int id) {

                    onAlertBoxSelected( 2,messageID);
                    dialog.dismiss();
                }
            });
        }

        try {

            ((Cocos2dxActivity) Cocos2dxActivity.getContext()).runOnUiThread(new Runnable() {

                @Override
                public void run() {
                    // create alert dialog
                    Dialog alertDialog = alertDialogBuilder.create();
                    // show it
                    alertDialog.show();
                }
            });


        }catch(Exception e){
            //Log.e(TAG_C_J, e.getMessage());
        }

    }


    public static native void onAlertBoxSelected(final int buttonIndex,final int messageID);

}
