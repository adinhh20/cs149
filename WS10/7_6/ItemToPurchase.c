#include<stdio.h>
#include<string.h>

#include "ItemToPurchase.h"

void MakeItemBlank(ItemToPurchase* item) {
   strcpy(item->itemName, "none");
   (*item).itemPrice = 0;
   (*item).itemQuantity = 0;
}

int PrintItemCost(ItemToPurchase item){
   int total = item.itemQuantity * item.itemPrice;
   printf("%s %d @ $%d = $%d\n", item.itemName, item.itemQuantity, item.itemPrice, total);

   return total;

}