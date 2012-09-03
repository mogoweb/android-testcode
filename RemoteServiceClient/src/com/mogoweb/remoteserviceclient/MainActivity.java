package com.mogoweb.remoteserviceclient;

import android.app.Activity;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.ServiceConnection;
import android.os.Bundle;
import android.os.IBinder;
import android.os.RemoteException;
import android.util.Log;
import android.view.Menu;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;
import android.widget.ToggleButton;

import com.mogoweb.remoteservicetest.IStockQuoteService;

public class MainActivity extends Activity {
	private static final String TAG = "StockQuoteClient";
	private IStockQuoteService stockService = null;
	private ToggleButton bindBtn;
	private Button callBtn;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        
        bindBtn = (ToggleButton)findViewById(R.id.bindBtn);
        callBtn = (Button)findViewById(R.id.callBtn);
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.activity_main, menu);
        return true;
    }

    public void doClick(View view) {
    	switch(view.getId()) {
    	case R.id.bindBtn:
    		if(((ToggleButton) view).isChecked()) {
    			bindService(new Intent(
    					IStockQuoteService.class.getName()),
    					serConn, Context.BIND_AUTO_CREATE);
    		}
    		else {
    			unbindService(serConn);
    			callBtn.setEnabled(false);
    		}
    		break;
    	case R.id.callBtn:
    		callService();
    		break;
    	}
    }
    
    private void callService() {
    	try {
    		double val = stockService.getQuote("ANDROID");
    		Toast.makeText(MainActivity.this,
    				"Value from service is " + val,
    				Toast.LENGTH_SHORT).show();
    	} catch (RemoteException ee) {
    		Log.e("MainActivity", ee.getMessage(), ee);
    	}
    }

    private ServiceConnection serConn = new ServiceConnection() {
    	@Override
    	public void onServiceConnected(ComponentName name,
    			IBinder service)
    	{
    		Log.v(TAG, "onServiceConnected() called");
    		stockService = IStockQuoteService.Stub.asInterface(service);
    		bindBtn.setChecked(true);
    		callBtn.setEnabled(true);
    	}
    	
    	@Override
    	public void onServiceDisconnected(ComponentName name) {
    		Log.v(TAG, "onServiceDisconnected() called");
    		bindBtn.setChecked(false);
    		callBtn.setEnabled(false);
    		stockService = null;
    	}
    };
    
    protected void onDestroy() {
    	Log.v(TAG, "onDestroy() called");
    	if(callBtn.isEnabled())
    		unbindService(serConn);
    	super.onDestroy();
    }

}
