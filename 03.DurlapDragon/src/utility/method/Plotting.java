package utility.method;

import android.content.res.Resources;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.BitmapFactory.Options;
import android.util.TypedValue;

// ���֮��ķ��㺯������
public class Plotting
{
	/* 
	 * �ӹ�����Դ�е���һ��ͼƬ
	 * ʹ�ô˺������Խ���������⣺
	 * �����drawable��Դ�ж���ͼƬ�������ű������⵼�µ�ͼƬ������
	 */
	public static Bitmap decodeResourceNoScaled(Resources resObj,  int nId)
	{
	    TypedValue value = new TypedValue();
	    resObj.openRawResource(nId, value);
	    
	    Options opts = new Options();
	    // �˲����ǹؼ���ָ���ڲ�����ͼƬ��ʱ����ʹ�����ű���
	    opts.inScaled = false;
	    
	    return BitmapFactory.decodeResource(resObj, nId, opts);
	}

	/* 
	 * �������е�ͼƬ����ָ����С����
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
