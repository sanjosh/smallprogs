
void top_view(node * root) {

	static int count=0;

	if (root->left && count>=0) {
			count++;
			top_view(root->left);

	}

	printf("%d ", root->data);
	count--;

	if (root->right && count<0) {
			count--;
			top_view(root->right);
	}

}
