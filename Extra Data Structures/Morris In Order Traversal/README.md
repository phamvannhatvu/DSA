
# Thuật toán duyệt cây nhị phân trung thứ tự Morris
## Dẫn nhập
Duyệt cây (Tree Traversal) là một trong những thao tác cơ bản trên cây nhị phân. Duyệt cây được chia làm hai loại: duyệt theo chiều rộng (BFS) và duyệt theo chiều sâu (DFS), mỗi cách duyệt có những ưu nhược điểm riêng và phù hợp với những trường hợp khác nhau. Thông thường, thuật toán DFS thường được hiện thực bằng đệ quy hoặc các cấu trúc dữ liệu như Stack, [Thread](https://www.geeksforgeeks.org/threaded-binary-tree/), cả hai cách trên đều đòi hỏi thêm chi phí bộ nhớ cỡ $O(N)$. Do đó, các thuật toán với chi phí bộ nhớ nhỏ hơn đã được nghiên cứu, trong số đó thuật toán duyệt trung thứ tự Morris với độ phức tạp bộ nhớ $O(1)$ là một thuật toán tương đối dễ tiếp cận.
## Ý tưởng
Ý tưởng chính của thuật toán Morrris là thay đổi cấu trúc cây khi duyệt tới từng node một cách thuận tiện cho việc duyệt các node còn lại. Cụ thể, khi duyệt tới node **p**, nếu **p** không có node con trái, ta đánh dấu **p** đã được duyệt, sau đó duyệt cây con phải của **p**. Ngược lại, ta tìm node **q** đứng ngay trước **p** khi duyệt trung thứ tự (in order), cũng là node phải cùng trên cây con trái của **p**, sau đó gán **p** thành node con phải của **q**, rồi duyệt cây con trái của **p**. Khi đó, **p** sẽ được đánh dấu sau khi mọi node trên cây con trái của nó được đánh dấu.

![](https://live.staticflickr.com/65535/52702400514_21b74bfd93_m.jpg)  
Trường hợp node 1 không có node con trái, đánh dấu node 1 và đi tới node 2

![](https://live.staticflickr.com/65535/52702633828_42cab0c649_w.jpg)  
Trường hợp node 1 có node con trái, tìm node phải cùng của cây con trái (node 7) và gán node 1 thành node con phải của node 7, cây bị thay đổi cấu trúc như hình

![](https://live.staticflickr.com/65535/52701625257_98e026aca3.jpg)

#### Mã giả cho thuật toán Morrris
```pseudocode
Morris Algorithm:
while (not finised)
	if (node has left child)
		make node the right child of right-most node in left subtree
		go to the left child and remove it from node
	else 
		visit node
		go to the right child
```
Dễ nhận thấy, thuật toán này chỉ nên sử dụng như thao tác cuối cùng trên cây, bởi nó thay đổi toàn bộ cấu trúc của cây cần duyệt. Để khắc phục điều này, ta giữ nguyên node trái của các node được duyệt (thay vì xóa đi như cách hiện thực trên) và dùng phương pháp khác để xác định điều kiện đánh dấu một node. Cụ thể, khi toàn bộ cây con trái của một node được đánh dấu, node đó thay vì không có node con trái (như cách hiện thực trên) thì tạo thành một chu trình, dựa vào chu trình đó ta có thể xác định được điều kiện để đánh dấu node đang xét. Ví dụ, cho một cây có cấu trúc như hình:  

![](https://live.staticflickr.com/65535/52702783570_71a2af3292_w.jpg)

Theo cách hiện thực xóa node trái, khi duyệt tới node 1, cấu trúc cây bị thay đổi như sau:

![](https://live.staticflickr.com/65535/52702620934_37b44076cf_n.jpg)

Và khi toàn bộ cây con trái (gốc là node 5) đã được đánh dấu, ta đánh dấu node 1:

![](https://live.staticflickr.com/65535/52702620909_40f51f743b_n.jpg)

_Những node tô màu xanh là những node đã được đánh dấu, tại bước kế tiếp, node 1 sẽ được đánh dấu_  
Theo cách hiện thực không xóa node trái, khi duyệt tới node 1, cấu trúc cây gần như không thay đổi (chỉ có thêm một cạnh nối từ node 7 tới node 1):

![](https://live.staticflickr.com/65535/52702854773_84fa57a083_n.jpg)

Khi toàn bộ cây con trái (gốc là node 5) được duyệt, ta nhận thấy node 1 nằm trong một chu trình như hình vẽ, trạng thái này tương đương với trạng thái không có node con trái như cách hiện thực trước, do đó ta sẽ đánh dấu node 1 ở bước kế tiếp, đồng thời xóa cạnh nối node 7 với node 1 để khôi phục cấu trúc của cây.

![](https://live.staticflickr.com/65535/52702394966_4b339f6f4e_n.jpg)

Khi đó, cây có cấu trúc như ban đầu:

![](https://live.staticflickr.com/65535/52702403051_bb86e63bce_n.jpg)

## Hiện thực
```C++
#include <iostream>
#include "../../Library/BinaryTree.h"

template<class T>
class MorrisInOrderTree : public BinaryTree<T>
{
private:
    void morrisTraverseLast(Node<T> *root)
    {
        Node<T> *p = root;
        while (p != nullptr)
        {
            if (p->left == nullptr)
            {
                std::cout << p->value << ' ';
                p = p->right;
            }else
            {
                Node<T> *tmp = p->left;
                while (tmp->right != nullptr)
                {
                    tmp = tmp->right;
                }
                tmp->right = p;
                tmp = p->left;
                p->left = nullptr;
                p = tmp;
            }
        }
    }
public:
    //only call this method when no more operations need to be executed because it change the construct of the tree
    void morrisTraverseLast()
    {
        morrisTraverseLast(this->root);
    }

    void morrisTraverse()
    {
        Node<T> *p = this->root;

        while (p != nullptr)
        {
            if (p->left == 0)
            {
                std::cout << p->value << ' ';
                p = p->right;
            }else
            {
                Node<T> *tmp = p->left;
                while (tmp->right != p && tmp->right != 0) tmp = tmp->right;
                if (tmp->right == 0)
                {
                    tmp->right = p;
                    p = p->left;
                }else 
                {
                    tmp->right = 0;
                    std::cout << p->value << ' ';
                    p = p->right;
                }
            }
        }
    }
};
```
Trong đoạn code trên, hàm ```morrisTraverseLast()``` hiện thực phương pháp xóa node trái, còn hàm ```morrisTraverse()``` hiện thực phương pháp không xóa node trái, biến ```tmp``` được sử dụng tìm node liền trước khi duyệt trung thứ tự (```tmp->right == 0```), cũng như để xác định điều kiện đánh dấu node (nằm trong chu trình, ```tmp->right == p```).

## Đánh giá độ phức tạp
### Độ phức tạp không gian
Thuật toán Morris (trong cả 2 cách hiện thực) đều chỉ sử dụng thêm một số biến trỏ tới các node, do đó chi phí bộ nhớ là $O(1)$.

### Độ phức tạp thời gian
Đối với cách hiện thực xóa node trái, mỗi node được duyệt tới tối đa 2 lần: khi được duyệt qua để đi tìm node phải cùng và khi duyệt qua để đánh dấu. Thật vậy, mỗi node chỉ được sử dụng tối đa một lần để tìm node phải cùng của một cây con trái, sau đó, nó sẽ không thuộc bất kỳ một cây con trái nào, từ đó không được duyệt thêm một lần nào nữa (trừ khi duyệt để đánh dấu).

![](https://live.staticflickr.com/65535/52702777169_6262f21de8_n.jpg)

Khi duyệt tới node 1, các node 2, 4, 5 được duyệt để tìm ra node phải cùng của cây con trái (gốc là node 2). Sau đó, không có thời điểm nào các node này thuộc một cây con trái, do đó không được duyệt để tìm node phải cùng nữa.

![](https://live.staticflickr.com/65535/52703010108_b5293b2144_w.jpg)

![](https://live.staticflickr.com/65535/52702522046_4e4a50ab92_n.jpg)

![](https://live.staticflickr.com/65535/52702522076_d3d1efa63b_n.jpg)

Đối với cách hiện thực không xóa node trái, mỗi node được duyệt tới tối đa 3 lần, 2 lần như cách hiện thực trên và một lần khác để xác định các chu trình.  
Vậy, độ phức tạp thời gian trong cả hai cách hiện thực là $O(N)$.

## Nhận xét
Thuật toán Morris là một thuật toán duyệt cây khá dễ tiếp cận với độ phức tạp bộ nhớ $O(1)$ tối ưu hơn các thuật toán duyệt thông thường. Tuy nhiên, trong đa phần các trường hợp, thuật toán DFS bằng đệ quy vẫn được ưa chuộng vì tính thân thuộc với suy nghĩ tự nhiên.

## Công việc tương lai
Hiện thực thuật toán Morris cho các thứ tự khác (preorder và postorder).