# An item on the Starbucks Menu
class MenuItem:
    def __init__(self,line):
        a = line.split(',')
        self.name = a[0]
        self.cals = a[1]
        self.carbs = a[2]

    def __repr__(self):
        return self.name

    def __lt__(self, other):
        return self.cals < other.cals


# Test code
item1 = MenuItem("Chonga Bagel,300,50")
item2 = MenuItem("Cheese Danish,290,33")
item3 = MenuItem("Chocolate Chip Cookie,570,75")

item_list = [item1, item2, item3]
item_list.sort()
print(item_list)