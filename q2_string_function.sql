/*q2_string_function
Get all unique ShipNames from the Order table that contain a hyphen '-'.*/
SELECT distinct ShipName
FROM `Order`
WHERE ShipName LIKE '%-%'
ORDER BY ShipName;
