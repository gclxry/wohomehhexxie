// 推荐应用下载列表
package com.burlapdragon.main.gameentry.recommend;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import com.burlapdragon.main.R;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.BaseAdapter;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.ListView;
import android.widget.TextView;

public class RecommendDownListActivity extends Activity {

	private List<Map<String, Object>> mData = null;
	private ListView m_RecommendList = null;
	private View m_curShowView = null;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_recommend_list);

		mData = getData();

		RecommendAdapter adapter = new RecommendAdapter(this);

		m_RecommendList = (ListView) this.findViewById(R.id.RecommendList);
		m_RecommendList.setAdapter(adapter);

		m_RecommendList.setOnItemClickListener(new OnItemClickListener() {
			@Override
			public void onItemClick(AdapterView<?> arg0, View arg1, int arg2,
					long arg3) {
				// 其中arg0包含了你所有的数据星系，通过其配合arg2（被选中的项）即可得到你要的map信息了
				Map<String, Object> itemAtPosition = (Map<String, Object>) arg0
						.getItemAtPosition(arg2);
				// 然后通过map，使用关键词查找你需要的列表中的数据项，我是示例代码，后面的要自己改
				// String str = (String)itemAtPosition.get("info");

				showInfo("List", "---------");
			}
		});
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

	/*
	 * // ListView 中某项被选中后的逻辑
	 * 
	 * @Override protected void onListItemClick(ListView l, View v, int
	 * position, long id) {
	 * 
	 * Log.v("MyListView4-click", (String) mData.get(position).get("title")); }
	 */
	public class RecommendAdapter extends BaseAdapter {

		// //////////////////////////////////////////////////////////////////////////////////////////
		//
		public final class ViewHolder {
			public ImageView img = null;
			public TextView title = null;
			public TextView info = null;
			public Button viewBtn = null;
			public View hideView = null;
		}

		// //////////////////////////////////////////////////////////////////////////////////////////

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
				holder.hideView = (View) convertView
						.findViewById(R.id.ListViewBottomPanel);
				// holder.hideView.setVisibility(View.INVISIBLE);
				holder.hideView.setVisibility(View.GONE);
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

					View vParent = (View) v.getParent();
					if (vParent == null)
						return;

					View vParent1 = (View) vParent.getParent();
					if (vParent1 == null)
						return;

					View vShow = vParent1
							.findViewById(R.id.ListViewBottomPanel);
					if (vShow == null)
						return;

					if (m_curShowView != null)
						m_curShowView.setVisibility(View.GONE);

					if (m_curShowView == vShow) {
						m_curShowView.setVisibility(View.GONE);
						m_curShowView = null;
					} else {
						vShow.setVisibility(View.VISIBLE);
						m_curShowView = vShow;
					}
				}
			});

			return convertView;
		}
	}

	public void showInfo(String strTitle, String strInfo) {
		new AlertDialog.Builder(this).setTitle(strTitle).setMessage(strInfo)
				.setPositiveButton("确定", new DialogInterface.OnClickListener() {
					@Override
					public void onClick(DialogInterface dialog, int which) {
					}
				}).show();
	}
}
