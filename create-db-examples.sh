#!bin/bash

mkdir db-examples
cd db-examples

echo \
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>
<Database tablesCount=\"3\" accessMode=\"2\">
	<Table tableName=\"Teachers\" fieldsCount=\"3\" rowsCount=\"1\">
		<DisplayParams displayMode=\"0\" xCoord=\"199\" yCoord=\"182\" width=\"233\" heigh=\"36\"/>
		<DisplayParams displayMode=\"1\" xCoord=\"268\" yCoord=\"159\" width=\"234\" heigh=\"150\"/>
		<DisplayParams displayMode=\"2\" xCoord=\"240\" yCoord=\"194\" width=\"335\" heigh=\"105\"/>
		<Fields Name=\"String\" ID=\"int\" Subject=\"String\"/>
		<Row Name=\"Alex\" ID=\"322\" Subject=\"Math\"/>
	</Table>
	<Table tableName=\"Info\" fieldsCount=\"2\" rowsCount=\"7\">
		<DisplayParams displayMode=\"0\" xCoord=\"661\" yCoord=\"184\" width=\"301\" heigh=\"36\"/>
		<DisplayParams displayMode=\"1\" xCoord=\"714\" yCoord=\"159\" width=\"238\" heigh=\"120\"/>
		<DisplayParams displayMode=\"2\" xCoord=\"728\" yCoord=\"182\" width=\"234\" heigh=\"267\"/>
		<Fields Games=\"String\" ID=\"int\"/>
		<Row Games=\"CS:GO\" ID=\"01\"/>
		<Row Games=\"Dota 2\" ID=\"02\"/>
		<Row Games=\"BATTLEGROUNDS\" ID=\"03\"/>
		<Row Games=\"FIFA 17\" ID=\"04\"/>
		<Row Games=\"Split/Second\" ID=\"05\"/>
		<Row Games=\"Need for Speed\" ID=\"06\"/>
		<Row Games=\"CoD\" ID=\"07\"/>
	</Table>
	<Table tableName=\"Sport\" fieldsCount=\"3\" rowsCount=\"2\">
		<DisplayParams displayMode=\"0\" xCoord=\"414\" yCoord=\"393\" width=\"288\" heigh=\"36\"/>
		<DisplayParams displayMode=\"1\" xCoord=\"505\" yCoord=\"398\" width=\"237\" heigh=\"151\"/>
		<DisplayParams displayMode=\"2\" xCoord=\"397\" yCoord=\"527\" width=\"335\" heigh=\"132\"/>
		<Fields Name=\"String\" League=\"String\" Rating=\"int\"/>
		<Row Name=\"Football\" League=\"EPL\" Rating=\"1000\"/>
		<Row Name=\"value1\" League=\"La Liga\" Rating=\"995\"/>
	</Table>
	<Relation leftTableName=\"Teachers\" leftFieldName=\"ID\" rightTableName=\"Info\" rightFieldName=\"ID\"/>
</Database>" \
> example.xml
