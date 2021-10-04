/*Compute some statistics about categories of products*/
SELECT CategoryName,COUNT(*),ROUND(AVG(UnitPrice),2),
	MIN(UnitPrice),MAX(UnitPrice),SUM(UnitsOnOrder)
FROM Product,Category
WHERE Product.CategoryId=Category.Id /*and COUNT (*)>10*/
GROUP BY CategoryId
HAVING COUNT(*)>10
ORDER BY CategoryId;