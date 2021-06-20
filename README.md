## 基于八叉树分割的场景管理器和简易物理引擎的实现（Opnegl）
### 项目作者
西南交通大学 吴忌 
### 项目说明  
1.针对场景中物体数量过多且对所有物体进行同时渲染会降低帧率的问题,采用八叉树对三维场景进行递推切割。八叉树管理器既可以对场景中任意物体进行查找/增添/修改/删除,也可以快速查询与自身包围盒相交的场景包围盒,实现场景的动态加载,从而能权衡视野大小和渲染速度.  
2.针对遍历的方式进行碰撞检测负荷过大的问题,采用分离轴测试实现碰撞检测算法(主要为AABB、OBB和Sphere包围盒碰撞算法),并结合八叉树管理器实现简单的物理引擎,物理引擎中模拟了重力和弹力等效果,使用八叉树搜索的方式,将单个物体的相交检测速度由O(n)优化至O(log n).    
3.通过实现的场景管理器和物理引擎,开发了一个"我的世界"游戏,玩家以第一人称视角自由漫步在场景中,场景会根据玩家位置和柏林噪声动态加载,支持玩家自由放置具有碰撞特性的物体,物理引擎将模拟物体反弹的效果.  
### 使用说明
初始状态为模式1

按q进行切换(模式1：自身包围盒场景加载，模式2：全部场景加载（会使得帧率变低），模式3：加载离自身最近的分割子块包围盒)
按e切换为上帝视角
按m转换为线框模式
按n纸飞机和地球切换
按j可以向下抛出弹性物体
按k可以使得弹性物体静止（以提高帧率）
模式1下：按p可以扩大自身包围盒尺寸（帧率降低）
模式1下：按o可以减小自身包围盒尺寸（帧率提高）
### 演示视频
