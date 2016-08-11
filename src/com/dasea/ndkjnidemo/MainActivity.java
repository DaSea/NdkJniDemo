package com.dasea.ndkjnidemo;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;

public class MainActivity extends Activity {
    
    JniDemo jniDemo = null;
    Button testBasicDataButton = null;
    Button testObjectDataButton = null;
    Button testBasicArrDataButton = null;
    Button testStringArrDataButton = null;
    Button testObjectArrDataButton = null;
    Button testBasicDataRetButton = null;
    Button testStringDataRetButton = null;
    Button testObjectDataRetButton = null;
    Button testBasicDataArrRetButton = null;
    Button testStrDataArrRetButton = null;
    Button testObjDataArrRetButton = null;
    Button testStrDataRetByParamButton = null;
    Button testObjDataRetByParamButton = null;
    Button testArrDataRetByParamButton = null;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        
        jniDemo = new JniDemo();
        testBasicDataButton = (Button)findViewById(R.id.button1);
        testBasicDataButton.setOnClickListener(new BasicDataOnClickListener());
        
        testObjectDataButton = (Button)findViewById(R.id.button2);
        testObjectDataButton.setOnClickListener(new ObjectDataOnClickListener());
        
        testBasicArrDataButton = (Button)findViewById(R.id.button3);
        testBasicArrDataButton.setOnClickListener(new BasicArrDataOnClickListener());
        
        testStringArrDataButton = (Button)findViewById(R.id.button4);
        testStringArrDataButton.setOnClickListener(new StringArrDataOnClickListener());
        
        testObjectArrDataButton = (Button)findViewById(R.id.button5);
        testObjectArrDataButton.setOnClickListener(new ObjectArrDataOnClickListener());
        
        testBasicDataRetButton = (Button)findViewById(R.id.button6);
        testBasicDataRetButton.setOnClickListener(new BasicDataRetOnClickListener());
        
        testStringDataRetButton = (Button)findViewById(R.id.button7);
        testStringDataRetButton.setOnClickListener(new StringDataRetOnClickListener());
        
        testObjectDataRetButton = (Button)findViewById(R.id.button8);
        testObjectDataRetButton.setOnClickListener(new ObjectDataRetOnClickListener());
        
        testBasicDataArrRetButton = (Button)findViewById(R.id.button9);
        testBasicDataArrRetButton.setOnClickListener(new BasicDataArrRetOnClickListener());
        
        testStrDataArrRetButton = (Button)findViewById(R.id.button10);
        testStrDataArrRetButton.setOnClickListener(new StrDataArrRetOnClickListener());
        
        testObjDataArrRetButton = (Button)findViewById(R.id.button11);
        testObjDataArrRetButton.setOnClickListener(new ObjDataArrRetOnClickListener());
        
        testStrDataRetByParamButton = (Button)findViewById(R.id.button12);
        testStrDataRetByParamButton.setOnClickListener(new StrDataRetByParamOnClickListener());
        
        testObjDataRetByParamButton = (Button)findViewById(R.id.button13);
        testObjDataRetByParamButton.setOnClickListener(new ObjDataRetByParamOnClickListener());
        
        testArrDataRetByParamButton = (Button)findViewById(R.id.button14);
        testArrDataRetByParamButton.setOnClickListener(new ArrDataRetByParamOnClickListener());
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();
        if (id == R.id.action_settings) {
            return true;
        }
        return super.onOptionsItemSelected(item);
    }

    public class BasicDataOnClickListener implements OnClickListener {
        @Override
        public void onClick(View arg0) {
            boolean bdata = false;
            int idata = -1;
            double ddata = Math.PI;
            String sdataString = "Hello world!";
            Log.d("JniDemo", "testBasicData");
            jniDemo.testBasicData(bdata, idata, ddata, sdataString);
        }
    }
    public class ObjectDataOnClickListener implements OnClickListener {
        @Override
        public void onClick(View arg0) {
            JniData data = new JniData();
            data.bData = false;
            data.cData = 12;
            data.iData = 214;
            data.dData = 100.12;
            data.sData = "Test object!";
            for (int i = 0; i < data.byteArr.length; ++i) {
                data.byteArr[i] = (byte) (20 + i);
            }
            
            for (int i = 0; i < data.intArr.length; ++i) {
                data.intArr[i] = i*10 + 11;
            }
            
            jniDemo.testObjectData(data);
        }
    }
    public class BasicArrDataOnClickListener implements OnClickListener {
        @Override
        public void onClick(View arg0) {
            int arrInt[] = new int[]{1, 2, 4, 5, 6, 1, 6, 86, 22, 65};
            jniDemo.testBasicArrData(arrInt);
        }
    }
    public class StringArrDataOnClickListener implements OnClickListener {
        @Override
        public void onClick(View arg0) {
            String strArr[] = new String[]{"You", "Are", "Pig"};
            jniDemo.testStringArrData(strArr);
        }
    }
    public class ObjectArrDataOnClickListener implements OnClickListener {
        @Override
        public void onClick(View arg0) {
            JniData objArr[] = new JniData[]{new JniData(), new JniData()};
            objArr[0].bData = false;
            objArr[0].sData = "test arr1";
            
            objArr[1].sData = "test arr2!";
            jniDemo.testObjectArrData(objArr);
        }
    }
    public class BasicDataRetOnClickListener implements OnClickListener {
        @Override
        public void onClick(View arg0) {
            int data = jniDemo.testBasicDataRet();
            Log.d("JniDemo", "BasicDataRet: " + data);
        }
    }
    public class StringDataRetOnClickListener implements OnClickListener {
        @Override
        public void onClick(View arg0) {
            String data = jniDemo.testStringDataRet();
            Log.d("JniDemo", "StringDataRet: " + data);
        }
    }
    public class ObjectDataRetOnClickListener implements OnClickListener {
        @Override
        public void onClick(View arg0) {
            JniData jniData = (JniData)jniDemo.testObjectDataRet();
            Log.d("JniDemo", "JniData: " + jniData.sData + ", " + jniData.dData + ", " + jniData.iData);
            
            for (int i = 0; i < jniData.byteArr.length; i++) {
                Log.d("JniDemo", i + " -> " + jniData.byteArr[i]);
            }
            
            for (int i = 0; i < jniData.intArr.length; i++) {
                Log.d("JniDemo", i + " -> " + jniData.intArr[i]);
            }
        }
    }
    public class BasicDataArrRetOnClickListener implements OnClickListener {
        @Override
        public void onClick(View arg0) {
            int[] intArr = jniDemo.testBasicDataArrRet();
            String msg = "";
            for (int i = 0; i < intArr.length; i++) {
                msg = msg + intArr[i] + "; ";
            }
            
            Log.d("JniDemo", msg);
        }
    }
    public class StrDataArrRetOnClickListener implements OnClickListener {
        @Override
        public void onClick(View arg0) {
            String[] strArr = jniDemo.testStrDataArrRet();
            String msg = "";
            for (int i = 0; i < strArr.length; i++) {
                msg = msg + strArr[i] + "; ";
            }
            Log.d("JniDemo", msg);
        }
    }
    public class ObjDataArrRetOnClickListener implements OnClickListener {
        @Override
        public void onClick(View arg0) {
            JniData[] objArr = jniDemo.testObjDataArrRet();
            String msg = "";
            for (int i = 0; i < objArr.length; i++) {
                msg = msg + objArr[i].sData + "; ";
            }
            Log.d("JniDemo", msg);
        }
    }
    public class StrDataRetByParamOnClickListener implements OnClickListener {
        @Override
        public void onClick(View arg0) {
            String string = new String("test hello");
            jniDemo.testStrDataRetByParam(string);
            
            Log.d("JniDemo", "字符串作为参数返回: " + string);
        }
    }
    public class ObjDataRetByParamOnClickListener implements OnClickListener {
        @Override
        public void onClick(View arg0) {
            JniData objData = new JniData();
            jniDemo.testObjDataRetByParam(objData);
            
            Log.d("JniDemo", "实体作为参数返回: " + objData.sData);
        }
    }
    public class ArrDataRetByParamOnClickListener implements OnClickListener {
        @Override
        public void onClick(View arg0) {
            int arrInt[] = new int[]{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
            jniDemo.testArrDataRetByParam(arrInt, arrInt.length);
            
            String msg = "";
            for (int i = 0; i < arrInt.length; i++) {
                msg = msg + arrInt[i] + ", ";
            }
            Log.d("JniDemo", msg);
        }
    }
}
