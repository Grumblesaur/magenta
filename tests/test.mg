type node {
	int value, node left, node right
}

func attach(node parent, node child) : node {
	print parent.value;
	print child.value;
	if not parent.left {
		node x = {parent.value, child, parent.right};
		print 1;
		return x;
	}
	print 2;
	return nil;
}

node root = {0, nil, nil};
print root.value;
print root.left;
print root.right;

node leaf = {-1, nil, nil};

node y = attach(root, leaf);
