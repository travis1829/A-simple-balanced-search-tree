class Node:
    def __init__(self, key, timer):
        self.key = key
        self.left = None
        self.right = None
        self.timer = timer

    def getCopy(self):
        copy = Node(self.key, self.timer)
        copy.left = self.left
        copy.right = self.right
        return copy

class SBST:
    """
    A simple, balanced, binary search tree.
    Use a K value in (0, 1).
    """
    #---Initialize---
    def __init__(self, k=0.9):
        if not(0 < k and k < 1):
            raise ValueError("k must be 0 < k < 1")
        self.__root = None
        self.__k = k
        self.__defaultTimer = 5

    #---Interface---
    def search(self, key):
        return self.__search(self.__root, key)

    def insert(self, key):
        (self.__root, result) = self.__insert(self.__root, key)
        return result

    def delete(self, key):
        (self.__root, result) = self.__delete(self.__root, key)
        return result

    def inorder(self, callbackFunction):
        self.__inorder(self.__root, callbackFunction)
    
    #---Private Methods---
    def __search(self, node, key):
        if node == None:
            return False
        elif key < node.key:
            return self.__search(node.left, key)
        elif node.key < key:
            return self.__search(node.right, key)
        else:
            return True

    def __insert(self, node, key):
        if node == None:
            return (Node(key, self.__defaultTimer), True)
        elif key < node.key:
            (node.left, result) = self.__insert(node.left, key)
        elif node.key < key:
            (node.right, result) = self.__insert(node.right, key)
        else:
            return (node, False)

        self.__update(node)
        return (node, result)
    
    def __delete(self, node, key):
        def getMax(node):
            if node.right == None:
                return node
            return getMax(node.right)
        
        if node == None:
            return (None, False)
        elif key < node.key:
            (node.left, result) = self.__delete(node.left, key)
        elif node.key < key:
            (node.right, result) = self.__delete(node.right, key)
        else:               
            if node.left and node.right:
                node.key = getMax(node.left).key
                (node.left, result) = self.__delete(node.left, node.key)
            elif node.left:
                return (node.left, True)
            elif node.right:
                return (node.right, True)
            else:
                return (None, True)

        self.__update(node)
        return (node, result)
    
    def __update(self, node):
        node.timer -= 1
        if node.timer <= 0:
            self.__rebuild(node)

    def __rebuild(self, node):
        if type(node) != Node:
            return
        def inorderNodeList(node, nodeList):
            if node == None:
                return
            inorderNodeList(node.left, nodeList)
            nodeList.append(node)
            inorderNodeList(node.right, nodeList)
        
        def buildBalancedTree(nodeList, start, end, k):
            if start > end:
                return None
            node = nodeList[(start+end)//2]
            node.left = buildBalancedTree(nodeList, start, (start+end)//2-1, k)
            node.right = buildBalancedTree(nodeList, (start+end)//2+1, end, k)
            node.timer = max(self.__defaultTimer, int(k*(end-start+1)))
            return node

        nodeList = []
        inorderNodeList(node.getCopy(), nodeList)
        newNode = buildBalancedTree(nodeList, 0, len(nodeList)-1, self.__k)
        (node.key, node.timer, node.left, node.right) = (newNode.key, newNode.timer, newNode.left, newNode.right)

    def __inorder(self, node, callback):
        if node == None:
            return
        self.__inorder(node.left, callback)
        callback(node.key)
        self.__inorder(node.right, callback)


    #---Special Methods---
    def __repr__(self):
        keyList = []
        self.__inorder(self.__root, keyList.append)
        return repr(keyList)

    def __iter__(self):
        def inorderYield(node):
            if node == None:
                return
            yield from inorderYield(node.left)
            yield node.key
            yield from inorderYield(node.right)
            
        return inorderYield(self.__root)
        
    #---Analysis Tools---
    def __debug(self, node, depth):
        if node == None:
            return
        self.__debug(node.left, depth+1)
        print(format(node.key, ">7"), format(node.timer, ">7"), format(depth, ">7"))
        self.__debug(node.right, depth+1)

    def debug(self):
        print("    key   timer   depth")
        self.__debug(self.__root, 0)

#---Example Usage---
if __name__ == "__main__":
    tree = SBST()
    tree.insert(10)
    tree.insert(15)
    tree.insert(20)
    if tree.search(20) == True:
        print("found")

    tree.delete(20)
    if  tree.search(20) == False:
        print("not found")
