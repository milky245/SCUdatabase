/*Concatenate the ProductNames ordered by the Company 'Queen
Cozinha' on 2014-12-25*/
SELECT ProductName, P.Id, rank() OVER (ORDER BY P.Id) AS IdRank
FROM Product P, OrderDetail, `Order` O, Customer
WHERE P.Id=OrderDetail.ProductId AND OrderDetail.OrderId=O.Id AND O.CustomerId=Customer.Id 
	AND Customer.CompanyName =  'Queen Cozinha' AND O.OrderDate LIKE '2014-12-25%'
ORDER BY P.Id