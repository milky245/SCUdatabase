/*Indicate if an order's ShipCountry is in North America. For our purposes, this 
is 'USA', 'Mexico', 'Canada'*/
SELECT Id, ShipCountry||' | '||
CASE WHEN ShipCountry IN ('USA','Mexico','Canada') THEN 'NorthAmerica'
	ELSE 'OtherPlace' END AS CountryPlace
FROM `Order`
WHERE Id >=15445
ORDER BY Id
limit 0,20;