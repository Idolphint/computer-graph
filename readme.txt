3DS文件结构 

MAIN3DS (0x4D4D) //基本信息块
　　 |
　　 +--VERSION (0x0002) //版本信息块
　　 |
　　 +--EDIT3DS (0x3D3D) //编辑信息块
　　 | |
　　 | +--EDIT_MATERIAL (0xAFFF) //材质
　　 | | |
　　 | | +--MAT_NAME01 (0xA000) //材质名称
　　 | | +--MAT_AMBCOL (0xA010) //环境色
　　 | | +--MAT_DIFCOL (0xA020) //漫射色
　　 | | +--MAT_SPECOL (0xA030) //反射色
　　| | +--MAT_SHININESS (0xA040) //亮度
　　| | +--MATMAP (0xA200) //材质的纹理？？？？？ 
　　| | +--MATMAPFILE (0xA300) //保存纹理的文件名
　　 | |
　　 | +--EDIT_CONFIG1 (0x0100) //配置信息1
　　 | +--EDIT_CONFIG2 (0x3E3D) //配置信息2
　　 | +--EDIT_VIEW_P1 (0x7012) //视窗1
　　 | | |
　　 | | +--TOP (0x0001) //顶视图
　　 | | +--BOTTOM (0x0002) //底视图
　　 | | +--LEFT (0x0003) //左视图
　　 | | +--RIGHT (0x0004) //右视图
　　 | | +--FRONT (0x0005) //前视图
　　 | | +--BACK (0x0006) //后视图
　　 | | +--USER (0x0007) //用户自定义
　　 | | +--CAMERA (0xFFFF) //相机
　　 | | +--LIGHT (0x0009) //灯光
　　 | | +--DISABLED (0x0010) //禁用
　　 | | +--BOGUS (0x0011) //虚拟
　　 | |
　　 | +--EDIT_VIEW_P2 (0x7011) //视窗2
　　 | | |
　　 | | +--TOP (0x0001) //顶视图
　　 | | +--BOTTOM (0x0002) //底视图
　　 | | +--LEFT (0x0003) //左视图
　　 | | +--RIGHT (0x0004) //右视图
　　 | | +--FRONT (0x0005) //前视图
　　 | | +--BACK (0x0006) //后视图
　　 | | +--USER (0x0007) //用户自定义
　　 | | +--CAMERA (0xFFFF) //相机
　　 | | +--LIGHT (0x0009) //灯光
　　 | | +--DISABLED (0x0010) //禁用
　　 | | +--BOGUS (0x0011) //虚拟
　　 | |
　　 | +--EDIT_VIEW_P3 (0x7020) //视窗3
　　 | +--EDIT_VIEW1 (0x7001) //视图
　　 | +--EDIT_BACKGR (0x1200) //背景
　　 | +--EDIT_AMBIENT (0x2100) //环境
　　 | +--EDIT_OBJECT (0x4000) //对象（包括面、点等信息）
　　 | | |
　　 | | +--OBJ_TRIMESH (0x4100) //三角形网格对象
　　 | | | |
　　 | | | +--TRI_VERTEX (0x4110) //顶点
　　 | | | +--TRI_VERTEXOPTIONS (0x4111) //顶点选项
　　 | | | +--TRI_MAPPINGCOORS (0x4140) //纹理映射坐标
　　 | | | +--TRI_MAPPINGSTANDARD (0x4170) //标准映射
　　 | | | +--TRI_FACEL1 (0x4120) //面
　　| | | +--TRI_SMOOTH (0x4150) //
　　 | | | +--TRI_MATERIAL (0x4130) //材质名称
　　 | | | +--TRI_LOCAL (0x4160) //
　　 | | | +--TRI_VISIBLE (0x4165) //可见与否
　　 | | |
　　 | | +--OBJ_LIGHT (0x4600) //灯光
　　 | | | |
　　 | | | +--LIT_OFF (0x4620)
　　 | | | +--LIT_SPOT (0x4610)
　　 | | | +--LIT_UNKNWN01 (0x465A) //未知块
　　 | | | 
　　 | | +--OBJ_CAMERA (0x4700)
　　 | | | |
　　 | | | +--CAM_UNKNWN01 (0x4710) //未知块
　　 | | | +--CAM_UNKNWN02 (0x4720) //未知块
　　 | | |
　　 | | +--OBJ_UNKNWN01 (0x4710) //未知块
　　 | | +--OBJ_UNKNWN02 (0x4720) //未知块
　　 | |
　　 | +--EDIT_UNKNW01 (0x1100) //未知块
　　 | +--EDIT_UNKNW02 (0x1201) //未知块
　　 | +--EDIT_UNKNW03 (0x1300) //未知块
　　 | +--EDIT_UNKNW04 (0x1400) //未知块
　　 | +--EDIT_UNKNW05 (0x1420) //未知块
　　 | +--EDIT_UNKNW06 (0x1450) //未知块
　　 | +--EDIT_UNKNW07 (0x1500) //未知块
　　 | +--EDIT_UNKNW08 (0x2200) //未知块
　　 | +--EDIT_UNKNW09 (0x2201) //未知块
　　 | +--EDIT_UNKNW10 (0x2210) //未知块
　　 | +--EDIT_UNKNW11 (0x2300) //未知块
　　 | +--EDIT_UNKNW12 (0x2302) //未知块
　　 | +--EDIT_UNKNW13 (0x2000) //未知块
　　 | +--EDIT_UNKNW14 (0xAFFF) //未知块
　　 |
　　 +--KEYF3DS (0xB000) //关键帧信息块
　　 |
　　 +--KEYF_UNKNWN01 (0xB00A) //未知块
　　 +--EDIT_VIEW1 (0x7001) //视图
　　 +--KEYF_FRAMES (0xB008) //帧
　　 +--KEYF_UNKNWN02 (0xB009) //未知块
　　 +--KEYF_OBJDES (0xB002) //对象描述？？？
　　 |
　　 +--KEYF_OBJHIERARCH (0xB010) //层级
　　 +--KEYF_OBJDUMMYNAME (0xB011) //虚拟体名称
　　 +--KEYF_OBJUNKNWN01 (0xB013) //未知块
　　 +--KEYF_OBJUNKNWN02 (0xB014) //未知块
　　 +--KEYF_OBJUNKNWN03 (0xB015) //未知块
　　 +--KEYF_OBJTRANSLATE (0xB020) //偏移
　　 +--KEYF_OBJROTATE (0xB021) //旋转
　　 +--KEYF_OBJSCALE (0xB022) //缩放
　　另外还有一些块是在整个文件中都会经常出现的，那就是颜色块
　　COL_RGB 0x0010 //RGB色彩模式，以float存放3个分量
　　COL_TRU 0x0011 //真彩色模式，以char存放3个分量
　　COL_UNKNOWN 0x0013 //未知块
　　SHI_PER 0x0030 //百分比亮度




可以看出来，图形以中心为轴表示坐标，并且需要一定的坐标转换


-90
0
10
5
-300
-300
（成为了直线）
70
0
0
10
-300
0
---------------
x:0y:1z:0
x:-0y:1z:0
x:0y:-1z:0
x:0y:-1z:0
x:-1y:1.90735e-007z:-5.72205e-007
x:-1y:-3.8147e-007z:-0
x:4.76837e-007y:2.86102e-007z:-1
x:9.53674e-008y:-9.53674e-008z:-1
x:1y:1.19209e-007z:2.26498e-007
x:1y:1.54972e-007z:2.6226e-007
x:-2.26498e-007y:-2.26498e-007z:1
x:-2.6226e-007y:-1.90735e-007z:1

x:-0y:-0.173647z:-0.984808
x:-5.2518e-008y:-0.173647z:-0.984808
x:0y:0.173647z:0.984808
x:-6.49236e-009y:0.173647z:0.984808
x:-1y:-5.96632e-007z:-8.84759e-008
x:-1y:6.6241e-008z:3.75674e-007
x:4.83048e-007y:-0.984808z:0.173646
x:0y:-0.984808z:0.173647
x:1y:2.02356e-007z:-1.56729e-007
x:1y:2.31366e-007z:-1.98158e-007
x:-2.51357e-007y:0.984808z:-0.173647
x:-2.27197e-007y:0.984808z:-0.173647
