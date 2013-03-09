// 定义工程内部通用的值
package com.burlapdragon.common;

public class CommonDefines {
	// 一级场景单元格横向的默认个数
	public final static int FIRST_LEVEL_CELL_H_CTNS = 12;
	// 一级场景单元格横向的可活动的默认个数
	public final static int FIRST_LEVEL_CELL_H_ACTIVE_CTNS = (FIRST_LEVEL_CELL_H_CTNS - 1);
	// 一级场景单元格纵向的默认个数
	public final static int FIRST_LEVEL_CELL_V_CTNS = 8;
	// 游戏一帧所要用的时间，单位：毫秒
	public final static int GAME_ONE_FRAME_TIME = 30;
	// 通过一个单元需要的动画帧数
	public final static int ONE_CELL_FRAME_CTNS = 30;
}
