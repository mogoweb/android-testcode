package com.mogoweb.remoteservicecomplexclient;

import android.app.Activity;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.ServiceConnection;
import android.os.Bundle;
import android.os.IBinder;
import android.os.RemoteException;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;
import android.widget.ToggleButton;

import com.mogoweb.remoteservicecomplex.IStockQuoteService;
import com.mogoweb.remoteservicecomplex.Person;

public class MainActivity extends Activity {
	protected static final String TAG = "StockQuoteClient2";
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
    		Person person = new Person();
    		person.setAge(47);
    		person.setName("Dave");
    		String response = stockService.getQuote("ANDROID", person);
    		Toast.makeText(MainActivity.this,
    				"Value from service is "+response,
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
    	if(callBtn.isEnabled())
    		unbindService(serConn);
    	super.onDestroy();
    }

}
