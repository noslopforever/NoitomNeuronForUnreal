2015-9-11：
	noslopforever

	本模块主要处理链接NeuronAxis、获取数据、执行控制、以及模拟骨架在游戏中的展示和调试。
	NeuronAxis需选择为ZYX数据输出模式。

	底层调用
	-	基本思路
		通过Singleton来建立连接Source，然后侦听Source的回调，来获取SourceActor。
		SourceActor内保存当前帧动画数据。

	上层调用
	-	基本思路

		首先通过必要时刻调用包装器的Connect，确保连接到必要的Source。
		通过UNeuronAnimInstance来得到每一帧的Animation数据。

	工具和辅助
