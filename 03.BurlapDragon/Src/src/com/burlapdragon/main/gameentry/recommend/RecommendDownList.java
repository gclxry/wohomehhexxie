// 推荐应用下载列表
package com.burlapdragon.main.gameentry.recommend;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import com.burlapdragon.main.R;

import android.app.AlertDialog;
import android.app.ListActivity;
import android.content.Context;
import android.content.DialogInterface;
import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.ListView;
import android.widget.TextView;

public class RecommendDownList extends ListActivity {

	private List<Map<String, Object>> mData = null;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		mData = getData();
		
		RecommendAdapter adapter = new RecommendAdapter(this);
        setListAdapter(adapter);
	}

	private List<Map<String, Object>> getData() {
		List<Map<String, Object>> list = new ArrayList<Map<String, Object>>();

		Map<String, Object> map = new HashMap<String, Object>();
		map.put("title", "G1");
		map.put("info", "google 1");
		map.put("img", R.drawable.dragon2);
		list.add(map);

		map = new HashMap<String, Object>();
		map.put("title", "G2");
		map.put("info", "google 2");
		map.put("img", R.drawable.dragon3);
		list.add(map);

		map = new HashMap<String, Object>();
		map.put("title", "G3");
		map.put("info", "google 3");
		map.put("img", R.drawable.ic_launcher);
		list.add(map);

		return list;
	}

	// ListView 中某项被选中后的逻辑
	@Override
	protected void onListItemClick(ListView l, View v, int position, long id) {

		Log.v("MyListView4-click", (String) mData.get(position).get("title"));
	}

	
	public class RecommendAdapter extends BaseAdapter {

////////////////////////////////////////////////////////////////////////////////////////////
		//
		public final class ViewHolder {
			public ImageView img;
			public TextView title;
			public TextView info;
			public Button viewBtn;
		}

////////////////////////////////////////////////////////////////////////////////////////////

		private LayoutInflater mInflater = null;

		public RecommendAdapter(Context context) {
			mInflater = LayoutInflater.from(context);
		}

		@Override
		public int getCount() {
			return mData.size();
		}

		@Override
		public Object getItem(int position) {
			return null;
		}

		@Override
		public long getItemId(int position) {
			return 0;
		}

		@Override
		public View getView(int position, View convertView, ViewGroup parent) {

			ViewHolder holder = null;

			if (convertView == null) {

				holder = new ViewHolder();

				convertView = mInflater.inflate(R.layout.list_recommend_style,
						null);

				holder.img = (ImageView) convertView.findViewById(R.id.itemImg);
				holder.title = (TextView) convertView
						.findViewById(R.id.itemText1);
				holder.info = (TextView) convertView
						.findViewById(R.id.itemText2);
				holder.viewBtn = (Button) convertView
						.findViewById(R.id.itemButton);
				convertView.setTag(holder);

			} else {
				holder = (ViewHolder) convertView.getTag();
			}

			holder.img.setBackgroundResource((Integer) mData.get(position).get(
					"img"));
			holder.title.setText((String) mData.get(position).get("title"));
			holder.info.setText((String) mData.get(position).get("info"));

			holder.viewBtn.setOnClickListener(new View.OnClickListener() {

				@Override
				public void onClick(View v) {
					showInfo();
				}
			});

			return convertView;
		}
	}

	/**
	 * listview中点击按键弹出对话框
	 */
	public void showInfo() {
		new AlertDialog.Builder(this).setTitle("我的listview")
				.setMessage("介绍...")
				.setPositiveButton("确定", new DialogInterface.OnClickListener() {
					@Override
					public void onClick(DialogInterface dialog, int which) {
					}
				}).show();

	}
}
