package utility.method;

import android.content.res.Resources;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.BitmapFactory.Options;
import android.util.TypedValue;

// 测绘之类的方便函数的类
public class Plotting
{
	/* 
	 * 从工程资源中导入一张图片
	 * 使用此函数可以解决如下问题：
	 * 解决从drawable资源中读入图片由于缩放比例问题导致的图片被缩放
	 */
	public static Bitmap decodeResourceNoScaled(Resources resObj,  int nId)
	{
	    TypedValue value = new TypedValue();
	    resObj.openRawResource(nId, value);
	    
	    Options opts = new Options();
	    // 此参数是关键，指挥内部导入图片的时候不再使用缩放比例
	    opts.inScaled = false;
	    
	    return BitmapFactory.decodeResource(resObj, nId, opts);
	}

	/* 
	 * 将工程中的图片按照指定大小读入
	 */
	public static Bitmap decodeResourceBySize(Resources resObj,  int nId, int nWidth, int nHeight)
	{
	    TypedValue value = new TypedValue();
	    resObj.openRawResource(nId, value);
	    
	    Options opts = new Options();
	    opts.inScaled = false;

		Bitmap bmpFrom = BitmapFactory.decodeResource(resObj, nId, opts);
		Bitmap bmpRet = Bitmap.createScaledBitmap(bmpFrom, nWidth, nHeight,
				true);
		bmpFrom.recycle();
		bmpFrom = null;
		return bmpRet;
	}
}
