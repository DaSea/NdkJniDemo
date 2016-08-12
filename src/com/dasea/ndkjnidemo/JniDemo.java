/**
 *
 */
package com.dasea.ndkjnidemo;

import java.nio.ByteBuffer;

import android.util.Log;

/**
 * @author DaSea
 *
 */
public class JniDemo {
  // DONE:0 写完基本数据类型及其数组类型的测试接口
  private static final String TAG = "JniDemo";
  static {
	  System.loadLibrary("ndkjnidemo");
  }
  
  // 测试directbuffer用的
  public native void setDirectBuffer(ByteBuffer buffer,int len);
  public native void testDirectBufferContext(int len);
  
  // 测试动态注册的
  public native String testDynamicRegister();
  
  // 测试基本数据
  public native void testBasicData(boolean bData, int iData, double dData, String sData);
  // 测试Object数据
  public native void testObjectData(JniData data);
  // 测试基本类型的数组类型
  public native void testBasicArrData(int[] data);
  // 测试Object的数组类型
  public native void testStringArrData(String[] strArr);
  public native void testObjectArrData(JniData[] objArr);

  // 测试数据类型的返回
  // 返回基本数据类型
  public native int testBasicDataRet();
  // 返回String类型
  public native String testStringDataRet();
  // 返回Object类型
  public native JniData testObjectDataRet();
  // 返回数组
  public native int[] testBasicDataArrRet();
  public native String[] testStrDataArrRet();
  public native JniData[] testObjDataArrRet();
  // 对于引用类型采用形参返回
  public native void testStrDataRetByParam(String strRet);
  public native void testObjDataRetByParam(JniData objRet);
  public native void testArrDataRetByParam(int[] arrRet, int length);

  // 用于测试c++调用java的接口
  public native void testCppCallJava();

  // c++ 调用 java
  public static void testvoidfunc(double dData, float fData) {
    String msg = String.format("Cpp->java: %f, %f", dData, fData);
    Log.d(TAG, msg);
  }

  public int testC2JByBasicData(double dData, float fData) {
    debugOut("Cpp->java: %f, %f", dData, fData);
    return 28;
  }

  public byte[] testC2JByArrData(short sData) {
    debugOut("Cpp->java: %d", sData);
    return new byte[]{'a', 'b', 'c'};
  }
  public String testC2JByStrData(int index, JniData objData, double value) {
    debugOut("Cpp->java: %d, %f", index, value);
    debugOut("Cpp->java: %d %f %c", objData.iData, objData.dData, objData.cData);
    return new String("Hello, c++, i am java!");
  }
  public String[] testC2JByStrArr(String strData) {
    Log.d(TAG, strData);

    return new String[]{"Hello", "Jni"};
  }
  public JniData testC2JByObjData(String strObj) {
    Log.d(TAG, strObj);

    return (new JniData());
  }
  public JniData[] testC2JByObjArr() {
    return (new JniData[2]);
  }

  // 调试接口
  private void debugOut(String format, Object... args) {
    String msg = String.format(format, args);
    Log.d(TAG, msg);
  }
}
