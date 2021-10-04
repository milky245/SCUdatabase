/*For each of the 8 discontinued products in the database, which customer made the 
first ever order for the product? Output the customer's CompanyName and ContactName*/

/*SELECT ProductName, CompanyName, ContactName
FROM (SELECT *,RANK() OVER(ORDER BY Id)AS ProductRank
	FROM Product WHERE Product.Discontinued=0)Discontinued
WHERE Discontinued.ProductRank
ORDER BY ProductName;*/
SELECT ProductName, CompanyName, ContactName
FROM (SELECT * FROM(SELECT * 
	FROM `Order` ORDER BY OrderDate) AS SortedOrder
	/*OrderDetail, Customer, Product*/
	LEFT OUTER JOIN OrderDetail ON SortedOrder.Id=OrderId
	LEFT OUTER JOIN Product ON ProductId=Product.Id
	LEFT OUTER JOIN Customer ON CustomerId=Customer.Id)
/*WHERE SortedOrder.Id=OrderDetail.Id AND CustomerId=Customer.Id AND ProductId=Product.Id*/
WHERE Discontinued=1
GROUP BY ProductName
ORDER BY ProductName;
