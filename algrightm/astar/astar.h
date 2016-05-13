/*
     A star algorithm
	
	 hqwsky,2016.5.13

*/
#ifndef __ASTRA_H__
#define __ASTRA_H__

/* 条件编译选项
   VS2008 MSVC 0
   VS2010 MSVC 1
*/
#define MSVC08   1
#define MSVC10   0


#include<vector>

#include<functional>

typedef short uint16_t;

/* A* algorithm */
class AStar
{
public:
	/*
	二维坐标
	*/
	struct Vec2
	{
		uint16_t x;
		uint16_t y;

		Vec2()
			: x(0)
			, y(0)
		{
		}

		Vec2(uint16_t _x, uint16_t _y)
			: x(_x)
			, y(_y)
		{
		}

		void set(uint16_t x, uint16_t y)
		{
			this->x = x;
			this->y = y;
		}

		bool operator== (const Vec2 &that) const
		{
			return x == that.x && y == that.y;
		}
	};

#if MSVC08
	typedef bool (*QueryFunction)(const Vec2&);   /// VS2008不支持匿名函数
#endif

#if MSVC10
	typedef std::function<bool(const Vec2&)> QueryFunction;
#endif


	/*
	参数
	*/
	struct Param
	{
		bool			corner;
		uint16_t		height;
		uint16_t		width;
		Vec2			start;
		Vec2			end;
		QueryFunction	can_reach;    

		Param()
			: height(0)
			, width(0)
			, corner(false)
			, can_reach(nullptr)
		{
		}
	};

     /**
	 * 路径节点状态
	 */
	enum NodeState
	{
		NOTEXIST,
		IN_OPENLIST,
		IN_CLOSELIST
	};
	
	/**
	 * 路径节点
	 */
	struct Node
	{ 
		uint16_t		g;        /// g(n)  
		uint16_t		h;        /// h(n)
		Vec2			pos;      /// 位置
		NodeState		state;    /// 标志
		Node*			parent;   /// 父结点

		int f() const
		{
			return g + h;
		}

		inline Node(const Vec2 &pos)
			: g(0)
			, h(0)
			, pos(pos)
			, parent(nullptr)
			, state(NOTEXIST)
		{
		}
	};

public:
	AStar();
	~AStar();

public:
	int stepValue() const;                  /// 平移步长

	int obliqueValue() const;               /// 斜移步长

	void setStepValue(int value);

	void setObliqueValue(int value);

	std::vector<Vec2> find(const Param &param);  /// main algorithm

private:
	void clear();

	void initParam(const Param &param);

	bool isVlidParam(const Param &param);

private:
	void percolateUp(size_t hole);

	bool getNodeIndex(Node *node, size_t &index);

	uint16_t calculGValue(Node *parent_node, const Vec2 &current_pos);

	uint16_t calculHValue(const Vec2 &current_pos, const Vec2 &end_pos);

	bool hasNoodeInOpenList(const Vec2 &pos, Node *&out);

	bool hasNodeInCloseList(const Vec2 &pos);

	bool canReach(const Vec2 &pos);

	bool canReach(const Vec2 &current_pos, const Vec2 &target_pos, bool allow_corner);

	void findCanReachPos(const Vec2 &current_pos, bool allow_corner, std::vector<Vec2> &can_reach);

	void handleFoundNode(Node *current_node, Node *target_node);

	void hndleNotFoundNode(Node *current_node, Node *target_node, const Vec2 &end_pos);

private:
	int						step_value_;
	int						oblique_value_;
	std::vector<Node *>		maps_;
	uint16_t				height_;
	uint16_t				width_;
	QueryFunction			query_;             /// 判断是否为障碍物
	std::vector<Node *>		open_list_;
};

#endif