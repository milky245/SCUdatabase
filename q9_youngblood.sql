/*Find the youngest employee serving each Region. If a Region is not served by an 
employee, ignore it*/
SELECT RegionDescription,FirstName,LastName,MAX(BirthDate)
/*FROM Employee,EmployeeTerritory,Territory,Region
WHERE Employee.Id=EmployeeTerritory.EmployeeId 
	AND Territory.Id=EmployeeTerritory.EmployeeId 
	AND Territory.RegionId=Region.Id*/
FROM Employee E,EmployeeTerritory ET,Territory T, Region R
WHERE E.Id=ET.EmployeeId AND T.Id=ET.TerritoryId AND T.RegionId=R.Id
GROUP BY R.Id
ORDER BY R.Id