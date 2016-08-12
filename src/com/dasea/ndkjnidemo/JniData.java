package com.dasea.ndkjnidemo;


/**
 * @author DaSea
 *
 */
public class JniData {
	static {
        init();
    }

    /**
     * 缓存类及其字段
     */
    private native static void init();
    
    public boolean bData;
    public double dData;
    public int iData;
    public byte cData;
    public String sData;
    public byte   byteArr[];
    public int 		intArr[];
    
    public JniData() {
        bData = true;
        dData = 100.11;
        iData = 333;
        cData = 100;
        sData = "20150204";
        byteArr = new byte[10];
        for (int i = 0; i < byteArr.length; ++i) {
            byteArr[i] = '2';
        }
        
        intArr = new int[10];
        for (int i = 0; i < intArr.length; ++i) {
            intArr[i] = i*10;
        }
    }
}
