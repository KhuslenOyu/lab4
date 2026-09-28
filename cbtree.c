#include "DS.h"

/*
  p-ийн зааж буй CBTree-д x утгыг оруулна
*/
void cb_push(CBTree *p, int x)
{
        p->tree.a[p->tree.len] = x;
        p->tree.len++;
}

/*
  p-ийн зааж буй CBTree-д idx индекстэй оройны зүүн хүүгийн индексийг буцаана.
  Зүүн хүү байхгүй бол -1 буцаана.
*/
int cb_left(const CBTree *p, int idx)
{
        int left = 2 * idx + 1;

        if (left >= p->tree.len)
                return -1;

        return left;
}

/*
  p-ийн зааж буй CBTree-д idx индекстэй оройны баруун хүүгийн индексийг буцаана.
  Баруун хүү байхгүй бол -1 буцаана.
*/
int cb_right(const CBTree *p, int idx)
{
        int right = 2 * idx + 2;

        if (right >= p->tree.len)
                return -1;

        return right;
}

/*
  p-ийн зааж буй CBTree-с x тоог хайн
  хамгийн эхэнд олдсон индексийг буцаана.
  Олдохгүй бол -1 утгыг буцаана.
*/
int cb_search(const CBTree *p, int x)
{
        int i;

        for (i = 0; i < p->tree.len; i++) {
                if (p->tree.a[i] == x)
                        return i;
        }

        return -1;
}

/*
  p-ийн зааж буй CBTree-д idx индекстэй зангилаанаас дээшхи бүх өвөг эцэгийг олох үйлдлийг хийнэ.
  Тухайн орой өөрөө өвөг эцэгт орохгүй.
  Өвөг эцэг бүрийг нэг шинэ мөрөнд хэвлэнэ. Өвөг эцэгийг доороос дээшхи дарааллаар хэвлэнэ.
*/
void cb_ancestors(const CBTree *p, int idx)
{
        if (idx <= 0 || idx >= p->tree.len)
                return;

        idx = (idx - 1) / 2;

        while (idx >= 0) {
                printf("%d\n", p->tree.a[idx]);

                if (idx == 0)
                        break;

                idx = (idx - 1) / 2;
        }
}

/*
  p-ийн зааж буй CBTree-ийн өндрийг буцаана
*/
int cb_height(const CBTree *p)
{
        int height = 0;
        int i = 0;

        if (p->tree.len == 0)
                return 0;

        while (i < p->tree.len) {
                height++;
                i = 2 * i + 1;
        }

        return height;
}

/*
  p-ийн зааж буй CBTree-д idx оройны ах, дүү оройн дугаарыг буцаана.
  Тухайн оройн эцэгтэй адил эцэгтэй орой.
  Ах, дүү нь байхгүй бол -1-г буцаана.
*/
int cb_sibling(const CBTree *p, int idx)
{
        if (idx <= 0 || idx >= p->tree.len)
                return -1;

        if (idx % 2 == 1) {
                if (idx + 1 < p->tree.len)
                        return idx + 1;
        } else {
                return idx - 1;
        }

        return -1;
}

/*
  p-ийн зааж буй CBTree-г idx дугаартай зангилаанаас эхлэн preorder-оор хэвлэ.
  Орой бүрийг нэг шинэ мөрөнд хэвлэнэ.
*/
void cb_preorder(const CBTree *p, int idx)
{
        int left, right;

        if (idx < 0 || idx >= p->tree.len)
                return;

        printf("%d\n", p->tree.a[idx]);

        left = cb_left(p, idx);
        right = cb_right(p, idx);

        cb_preorder(p, left);
        cb_preorder(p, right);
}

/*
  p-ийн зааж буй CBTree-г idx дугаартай зангилаанаас эхлэн in-order-оор хэвлэ.
  Орой бүрийг нэг шинэ мөрөнд хэвлэнэ.
*/
void cb_inorder(const CBTree *p, int idx)
{
        int left, right;

        if (idx < 0 || idx >= p->tree.len)
                return;

        left = cb_left(p, idx);
        right = cb_right(p, idx);

        cb_inorder(p, left);
        printf("%d\n", p->tree.a[idx]);
        cb_inorder(p, right);
}

/*
  p-ийн зааж буй CBTree-г idx дугаартай зангилаанаас эхлэн post-order-оор хэвлэ.
  Орой бүрийг нэг шинэ мөрөнд хэвлэнэ.
 */
void cb_postorder(const CBTree *p, int idx)
{
        int left, right;

        if (idx < 0 || idx >= p->tree.len)
                return;

        left = cb_left(p, idx);
        right = cb_right(p, idx);

        cb_postorder(p, left);
        cb_postorder(p, right);
        printf("%d\n", p->tree.a[idx]);
}

/*
  p-ийн зааж буй CBTree-с idx дугаартай зангилаанаас доошхи бүх навчийг олно.
  Навч тус бүрийн утгыг шинэ мөрөнд хэвлэнэ.
  Навчыг зүүнээс баруун тийш олдох дарааллаар хэвлэнэ.
*/
void cb_leaves(const CBTree *p, int idx)
{
       int left, right;

        if (idx < 0 || idx >= p->tree.len)
                return;

        left = cb_left(p, idx);
        right = cb_right(p, idx);

        if (left == -1 && right == -1) {
                printf("%d\n", p->tree.a[idx]);
                return;
        }

        cb_leaves(p, left);
        cb_leaves(p, right);
}

/*
  p-ийн зааж буй CBTree-д idx индекстэй оройноос доошхи бүх үр садыг хэвлэнэ.
  Тухайн орой өөрөө үр сад болохгүй.
  Үр, сад бүрийг нэг шинэ мөрөнд хэвлэнэ. Үр садыг pre-order дарааллаар хэлэх ёстой.
*/
void cb_descendants(const CBTree *p, int idx)
{
       int left, right;

        if (idx < 0 || idx >= p->tree.len)
                return;

        left = cb_left(p, idx);
        right = cb_right(p, idx);

        if (left != -1) {
                printf("%d\n", p->tree.a[left]);
                cb_descendants(p, left);
        }

        if (right != -1) {
                printf("%d\n", p->tree.a[right]);
                cb_descendants(p, right);
        }
}


/*
  p-ийн зааж буй Tree-д хэдэн элемент байгааг буцаана.
  CBTree-д өөрчлөлт оруулахгүй.
*/
int cb_size(const CBTree *p)
{
        return p->tree.len;
}


/*
  p-ийн зааж буй CBTree-д x утгаас үндэс хүртэлх оройнуудын тоог буцаана.
  x тоо олдохгүй бол -1-г буцаана.
*/
int cb_level(const CBTree *p, int x)
{
       int idx;
        int level = 0;

        idx = cb_search(p, x);

        if (idx == -1)
                return -1;

        while (idx > 0) {
                idx = (idx - 1) / 2;
                level++;
        }

        return level;
}

