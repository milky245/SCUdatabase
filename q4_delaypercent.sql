/*For each Shipper, find the percentage of orders which are late.*/
SELECT Delayed.CompanyName||' | '||
	ROUND(CAST(Delayed as DOUBLE)*100/CAST(Total as DOUBLE),2) AS Percentage
FROM (SELECT S.Id,S.CompanyName,COUNT(*) AS Delayed
	FROM `Order` O, Shipper S 
	WHERE O.ShippedDate>O.RequiredDate and O.ShipVia=S.Id GROUP BY S.Id)Delayed,
	(SELECT S.Id,S.CompanyName,COUNT(*) AS Total
	FROM `Order` O, Shipper S
	WHERE O.ShipVia=S.Id GROUP BY S.Id)Total
WHERE Delayed.Id=Total.Id
ORDER BY Percentage DESC;