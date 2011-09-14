package com.kokemono.android.gdd2011;

import com.google.android.apps.gddquiz.IQuizService;

import android.app.Activity;
import android.os.Bundle;
import android.os.IBinder;
import android.os.RemoteException;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.ServiceConnection;



public class MainActivity extends Activity {

	private EditText mEditText;
	private Button mButton;

	private IQuizService mQuizService = null;

	private ServiceConnection svcConn = new ServiceConnection() {

		@Override
		public void onServiceDisconnected(ComponentName name) {
			// TODO 自動生成されたメソッド・スタブ
			mQuizService = null;
		}

		@Override
		public void onServiceConnected(ComponentName name, IBinder service) {
			// TODO 自動生成されたメソッド・スタブ
			mQuizService = IQuizService.Stub.asInterface(service);
		}
	};


    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        mEditText = (EditText)findViewById(R.id.editText1);
        mButton = (Button)findViewById(R.id.button1);

        Intent intent = new Intent(IQuizService.class.getName());
        bindService(intent, svcConn, Context.BIND_AUTO_CREATE);


        mButton.setOnClickListener(new View.OnClickListener() {

			@Override
			public void onClick(View v) {
				// TODO 自動生成されたメソッド・スタブ
		        try {
					String devcode = mQuizService.getCode();
					 mEditText.setText(devcode);
				} catch (RemoteException e) {
					// TODO 自動生成された catch ブロック
					e.printStackTrace();
				}

			}
		});


   }
    public void onDestroy() {
        super.onDestroy();

        unbindService(svcConn);
    }

}