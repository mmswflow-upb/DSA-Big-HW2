#include <iostream>
#include <string>
using namespace std;

template <typename T>
class QuadTree {
public:
	T* info;
	
	QuadTree<T>* c1,*c2,*c3,*c4;
	QuadTree() {
		
		info = NULL;

		c1 = c2 = c3 = c4 = NULL;
	}
	void preOrderTraversal() {

		if (info != NULL) {
			cout << *this->info << " ";
		}
		else {
			return;
		}

		if (c1 != NULL) {

			c1->preOrderTraversal();
		}
		if (c2 != NULL) {

			c2->preOrderTraversal();
		}
		if (c3 != NULL) {

			c3->preOrderTraversal();
		}
		if (c4 != NULL) {

			c4->preOrderTraversal();
		}
	}

	void displayAllLevelsRec(int currLevel) {

		if (info != NULL) {

			string dashes = "";

			for (int i = 0; i < currLevel; i++) {
				dashes += "-";
			}

			cout << "\n" << dashes << *(info) << " ";

			if (*(info) == "p") {

				c1->displayAllLevelsRec(currLevel + 1);
				c2->displayAllLevelsRec(currLevel + 1);
				c3->displayAllLevelsRec(currLevel + 1);
				c4->displayAllLevelsRec(currLevel + 1);
			}
		}
	}

	void normalize() {

		if (info == NULL) {

			return;
		}

		if (*(info) == "p") {

			if (*(c1->info) == "b" || *(c1->info) == "w") {

				string color = *(c1->info);

				if (*(c2->info) == color) {

					if (*(c3->info) == color) {

						if (*(c4->info) == color) {

							c1 = NULL;
							c2 = NULL;
							c3 = NULL;
							c4 = NULL;

							*(info) = color;
						}
					}
				}
			}
		}
		return;
	}
};



template <typename T>
void createTreeFromPreOrder(QuadTree<T>* node, string& s) {

	node->info = new T;
	*(node->info) = s[0];

	if (s.length() == 1) {

		return;
	}

	if (*(node->info) == "p") {

		//If we have a p (multiple pixels, then we automatically assume we will get 4 pixels)

		s = s.substr(1, s.length());
		node->c1 = new QuadTree<T>;
		createTreeFromPreOrder(node->c1, s);

		s = s.substr(1, s.length());
		node->c2 = new QuadTree<T>;
		createTreeFromPreOrder(node->c2, s);

		s = s.substr(1, s.length());
		node->c3 = new QuadTree<T>;
		createTreeFromPreOrder(node->c3, s);

		s = s.substr(1, s.length());
		node->c4 = new QuadTree<T>;
		createTreeFromPreOrder(node->c4, s);

		node->normalize();
	}
	//read if it's p , read 4 children, if it's w or b create no children.
}

template <typename T>
void mergeQuadTrees(QuadTree<T>* t1, QuadTree<T>* t2, QuadTree<T>* node) {

	if (t1 == NULL && t2 == NULL) {
		node = NULL;
		return;
	}
	else if (t1 == NULL && t2 != NULL) {
		*node = *t2;
		return;
	}
	else if (t1 != NULL && t2 == NULL) {
		*node = *t1;
		return;
	}

	if (*(t1->info) == "b" || *(t2->info) == "b") {
		node->info = new T;
		*(node->info) = "b";
	}
	else if (*(t1->info) == "p" && *(t2->info) == "w") {
		*node = *t1;
		
	}
	else if (*(t1->info) == "w" && *(t2->info) == "p") {
		*node = *t2;
	}
	else if (*(t1->info) == "w" && *(t2->info) == "w") {
		node->info = new T;
		*(node->info) = "w";
		
	}
	else {//Both are of type "p", we must check all their children.

		node->info = new T;
		*(node->info) = "p";

		node->c1 = new QuadTree<T>;
		node->c2 = new QuadTree<T>;
		node->c3 = new QuadTree<T>;
		node->c4 = new QuadTree<T>;
		mergeQuadTrees(t1->c1, t2->c1, node->c1);
		mergeQuadTrees(t1->c2, t2->c2, node->c2);
		mergeQuadTrees(t1->c3, t2->c3, node->c3);
		mergeQuadTrees(t1->c4, t2->c4, node->c4);

		node->normalize();
	}
}


template <typename T>
void countBlackPixels(QuadTree<T>* t, int level, int& sum) {

	if (t->info == NULL) {
		return;
	}
	if (*(t->info) == "b") {

		sum += 1024 / (pow(4, level));
	}
	else if (*(t->info) == "p") {

		countBlackPixels(t->c1, level + 1, sum);
		countBlackPixels(t->c2, level + 1, sum);
		countBlackPixels(t->c3, level + 1, sum);
		countBlackPixels(t->c4, level + 1, sum);
	}
}



int main() {

	string op = "";
	string s1 = "";
	string s2 = "";

	QuadTree<string>* img1 = new QuadTree<string>;
	QuadTree<string>* img2 = new QuadTree<string>;
	QuadTree<string>* img3 = new QuadTree<string>;

	do{
		cout << "\n\n___________________________";

		cout << "\n\n1.Set Image\n2.Display Image\n3.Merge & Display Images\n4.Exit\nYour Option: ";
		cin >> op;

		if (op == "1") {

			cout << "\n\nSelect 1st or 2nd Image: ";
			cin >> op;

			if (op == "1") {

				cout << "\n\nType the preorder traversal for the 1st image: ";
				cin >> s1;
				createTreeFromPreOrder(img1, s1);
				
			}
			else if (op == "2") {

				cout << "\n\nType the preorder traversal for the 2nd image: ";
				cin >> s2;
				createTreeFromPreOrder(img2, s2);
			

			}else {
				cout << "Next time choose 1 or 2.";
				continue;
			}
		}
		else if (op == "2") {
			cout << "\n\nSelect 1st or 2nd Image: ";
			cin >> op;

			if (op == "1") {

				cout << "\n\nDisplaying the 1st image [BY LEVELS]: ";
				
				img1->displayAllLevelsRec(0);

				cout << "\n\nDisplaying the 1st Image [PREORDER]: ";
				img1->preOrderTraversal();

				int n = 0;
				countBlackPixels(img1,0, n);
				cout << "\n\nNumber of black pixels in the 1st image: " << n;
			}
			else if (op == "2") {

				cout << "\n\nDisplaying the 2nd image [BY LEVELS]: ";
				img2->displayAllLevelsRec(0);

				cout << "\n\nDisplaying the 2nd Image [PREORDER]: ";
				img2->preOrderTraversal();

				int n = 0;
				countBlackPixels(img2, 0, n);
				cout << "\n\nNumber of black pixels in the 2nd image: " << n;
			}
			else {
				cout << "Next time choose 1 or 2.";
				continue;
			}
		}
		else if (op == "3") {
			
			if (img1->info != NULL && img2->info != NULL) {

				mergeQuadTrees(img1, img2, img3);
			
				cout << "\n\nDisplaying the merged image [BY LEVELS]: ";
				img3->displayAllLevelsRec(0);

				cout << "\n\nDisplaying the 3rd Image [PREORDER]: ";
				img3->preOrderTraversal();

				int n = 0;
				countBlackPixels(img3, 0, n);
				cout << "\n\nNumber of black pixels in the merged image: " << n;
			}
			else {
				cout << "\n\nYou must set the 2 images first.";
				continue;
			}
		}
		else if (op == "4") {
			break;
		}
		else {
			cout << "\n\nChoose a valid option.";
			continue;
		}
	} while (true);
}