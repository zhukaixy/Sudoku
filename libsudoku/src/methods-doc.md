# 数独技巧

技巧来自[琳琅在线](http://www.llang.net/sudoku/skill/1.html)

## 具体技巧

1. 当一个格子只有一种可能性，那么可以确定该格子的值
2. 某一行（列/九宫）中，某个数字只有一个格子有可能性，那么可以确定该格子的值
3. 确定格的数字后需要排除其他格有这个数字的可能性

4. 同一行（列/九宫）中,两个格子有且仅有两个相同的可能性，则该行（列/九宫）中其他空格不可能有这两个数
5. 同一行（列/九宫）中,三个格子有且仅有三个相同的可能性，则该行（列/九宫）中其他空格不可能有这三个数

6. 同一行（列/九宫）中，仅有两个格子有可能有这两种可能性，则，这两个格子不可能有其他可能性
7. 同一行（列/九宫）中，仅有三个格子有可能有这三种可能性，则，这三个格子不可能有其他可能性

8. 在某一九宫格中，当所有可能出现某个数字的单元格都位于同一行（列）时，就可以把这个数字从该行（列）的其他单元格的候选数中删除；
9. 在某一行（列）中，当所有可能出现某个数字的单元格都位于同一九宫格中时，就可以把这个数字从该九宫格的其他单元格的候选数中删除。
10. 如果一个数字在某两行（列）中能填入的位置正好在同样的两列（行）中，则这两列（行）的其他的单元格中将不可能再出现这个数字；

## 技巧与实现对应关系

1. 唯一解法、唯余解法、唯一候选数法:
   SolveType.GridOnlyOnePosibility
2. 基础摒弃法、隐性唯一候选数法:
   SolveType.RowNumberOnlyOneGrid
   SolveType.ColNumberOnlyOneGrid
   SolveType.BlockNumberOnlyOneGrid
3. 区块摒弃法、候选数区块删减法:
   ImproveType.InBlockNumberInOneRow
   ImproveType.InBlockNumberInOneCol
   ImproveType.InRowNumberInBlock
   ImproveType.InColNumberInBlock
4. 矩形摒除法、候选数矩形删减法:
   ImproveType.TwoRowOneNumberInTwoCol
   ImproveType.TwoColOneNumberInTwoRow
5. 候选数对删减法:
   ImproveType.2GridWith2Posibility(Row, Column, Block)
6. 隐性候选数对删减法:
   ImproveType.2NumberIn2Grid(Row, Column, Block)
7. 三数集删减法:
   ImproveType.3GridWith3Posibility(Row, Column, Block)
8. 隐性三数集删减法:
   ImproveType.3NumberIn3Grid(Row, Column, Block)
9. 三链数删减法:
   ImproveType.ThreeRowOneNumberInThreeCol,
   ImproveType.ThreeColOneNumberInThreeRow

## 其他未实现操作

1. 3GridWith3Posibility 和 3NumberIn3Grid 的实现方式待改进，例如：12 23 13 的形式也属于这种情况
2. 组合摒除法
3. XY 形态匹配删减法
4. XYZ 形态匹配删减法
5. WXYZ 形态匹配删减法
