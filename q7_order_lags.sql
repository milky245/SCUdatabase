/*For the first 10 orders by CutomerId BLONP: get the Order's Id, OrderDate, 
previous OrderDate, and difference between the previous and current. Return 
results ordered by OrderDate (ascending)*/
SELECT Id,OrderDate,
	LAG(OrderDate,1)OVER(ORDER BY OrderDate)AS PreDate,
	ROUND(CAST(julianday(OrderDate) - julianday(LAG(OrderDate,1) 
	OVER(ORDER BY OrderDate)) AS FLOAT), 2)AS DateInterval
FROM `Order`
WHERE CustomerID='BLONP' 
ORDER BY OrderDate
LIMIT 0,10;