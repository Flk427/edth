DROP TABLE IF EXISTS "Economy";
CREATE TABLE "Economy" ("id" INTEGER PRIMARY KEY  NOT NULL  UNIQUE , "name" VARCHAR NOT NULL  UNIQUE );
INSERT INTO "Economy" VALUES(1,'Industrial');
INSERT INTO "Economy" VALUES(2,'Refinery');
INSERT INTO "Economy" VALUES(3,'Extraction');
INSERT INTO "Economy" VALUES(4,'Agriculture extraction');
DROP TABLE IF EXISTS "GoodGroups";
CREATE TABLE "GoodGroups" ("id" INTEGER PRIMARY KEY  AUTOINCREMENT  NOT NULL  UNIQUE , "position" INTEGER NOT NULL  UNIQUE , "name" TEXT UNIQUE );
INSERT INTO "GoodGroups" VALUES(0,20,'Consumer items');
INSERT INTO "GoodGroups" VALUES(1,30,'Foods');
INSERT INTO "GoodGroups" VALUES(2,10,'Chemicals');
INSERT INTO "GoodGroups" VALUES(4,40,'Industrial materials');
INSERT INTO "GoodGroups" VALUES(5,50,'Legal drugs');
INSERT INTO "GoodGroups" VALUES(6,60,'Machinery');
INSERT INTO "GoodGroups" VALUES(7,70,'Medicines');
INSERT INTO "GoodGroups" VALUES(8,80,'Metals');
INSERT INTO "GoodGroups" VALUES(9,90,'Minerals');
INSERT INTO "GoodGroups" VALUES(10,100,'Technology');
INSERT INTO "GoodGroups" VALUES(11,110,'Waste');
INSERT INTO "GoodGroups" VALUES(12,120,'Weapons');
INSERT INTO "GoodGroups" VALUES(13,105,'Textiles');
DROP TABLE IF EXISTS "GoodNames";
CREATE TABLE "GoodNames" ("id" INTEGER PRIMARY KEY  NOT NULL  UNIQUE , "name" TEXT NOT NULL  UNIQUE , "legal" BOOL NOT NULL , "group_id" INTEGER);
INSERT INTO "GoodNames" VALUES(1,'CHEMICAL DRUGS',1,NULL);
INSERT INTO "GoodNames" VALUES(2,'EXPLOSIVES',1,2);
INSERT INTO "GoodNames" VALUES(3,'HYDROGEN FUEL',1,2);
INSERT INTO "GoodNames" VALUES(4,'MINERAL OIL',1,NULL);
INSERT INTO "GoodNames" VALUES(5,'PESTICIDES',1,NULL);
INSERT INTO "GoodNames" VALUES(6,'CLOTHING',1,NULL);
INSERT INTO "GoodNames" VALUES(7,'CONSUMER TECHNOLOGY',1,NULL);
INSERT INTO "GoodNames" VALUES(8,'DOM. APPLIANCES',1,NULL);
INSERT INTO "GoodNames" VALUES(9,'BEER',1,NULL);
INSERT INTO "GoodNames" VALUES(10,'LIQUOR',1,NULL);
INSERT INTO "GoodNames" VALUES(11,'NARCOTICS',1,NULL);
INSERT INTO "GoodNames" VALUES(12,'TOBACCO',1,NULL);
INSERT INTO "GoodNames" VALUES(13,'WINE',1,NULL);
INSERT INTO "GoodNames" VALUES(14,'ALGAE',1,NULL);
INSERT INTO "GoodNames" VALUES(15,'ANIMAL MEAT',1,1);
INSERT INTO "GoodNames" VALUES(16,'COFFEE',1,1);
INSERT INTO "GoodNames" VALUES(17,'FISH',1,1);
INSERT INTO "GoodNames" VALUES(18,'FOOD CARTRIDGES',1,1);
INSERT INTO "GoodNames" VALUES(19,'FRUIT AND VEGETABLES',1,1);
INSERT INTO "GoodNames" VALUES(20,'GRAIN',1,1);
INSERT INTO "GoodNames" VALUES(21,'SYNTHETIC MEAT',1,1);
INSERT INTO "GoodNames" VALUES(22,'TEA',1,1);
INSERT INTO "GoodNames" VALUES(23,'ALLOYS',1,NULL);
INSERT INTO "GoodNames" VALUES(24,'PLASTICS',1,NULL);
INSERT INTO "GoodNames" VALUES(25,'POLYMERS',1,NULL);
INSERT INTO "GoodNames" VALUES(26,'SUPERCONDUCTORS',1,NULL);
INSERT INTO "GoodNames" VALUES(27,'SEMICONDUCTORS',1,NULL);
INSERT INTO "GoodNames" VALUES(28,'ATMOSPHERIC PROCESSORS',1,NULL);
INSERT INTO "GoodNames" VALUES(29,'CROP HARVESTERS',1,NULL);
INSERT INTO "GoodNames" VALUES(30,'MARINE EQUIPMENT',1,NULL);
INSERT INTO "GoodNames" VALUES(31,'HELIOSTATIC FURNACES',1,NULL);
INSERT INTO "GoodNames" VALUES(32,'MINERAL EXTRACTORS',1,NULL);
INSERT INTO "GoodNames" VALUES(33,'MICROBIAL FURNACES',1,NULL);
INSERT INTO "GoodNames" VALUES(34,'POWER GENERATORS',1,NULL);
INSERT INTO "GoodNames" VALUES(35,'WATER PURIFIERS',1,NULL);
INSERT INTO "GoodNames" VALUES(36,'AGRI-MEDICINES',1,NULL);
INSERT INTO "GoodNames" VALUES(37,'BASIC MEDICINES',1,NULL);
INSERT INTO "GoodNames" VALUES(38,'COMBAT STABILISERS',1,NULL);
INSERT INTO "GoodNames" VALUES(39,'PERFORMANCE ENHANCERS',1,NULL);
INSERT INTO "GoodNames" VALUES(40,'PROGENITOR CELLS',1,NULL);
INSERT INTO "GoodNames" VALUES(41,'ALUMINIUM',1,NULL);
INSERT INTO "GoodNames" VALUES(42,'BERYLLIUM',1,NULL);
INSERT INTO "GoodNames" VALUES(43,'COBALT',1,8);
INSERT INTO "GoodNames" VALUES(44,'COPPER',1,NULL);
INSERT INTO "GoodNames" VALUES(45,'GALLIUM',1,NULL);
INSERT INTO "GoodNames" VALUES(46,'GOLD',1,8);
INSERT INTO "GoodNames" VALUES(47,'INDIUM',1,NULL);
INSERT INTO "GoodNames" VALUES(48,'LITHIUM',1,NULL);
INSERT INTO "GoodNames" VALUES(49,'PALLADIUM',1,NULL);
INSERT INTO "GoodNames" VALUES(50,'PLATINUM',1,NULL);
INSERT INTO "GoodNames" VALUES(51,'SILVER',1,NULL);
INSERT INTO "GoodNames" VALUES(52,'TANTALUM',1,NULL);
INSERT INTO "GoodNames" VALUES(53,'TITANIUM',1,NULL);
INSERT INTO "GoodNames" VALUES(54,'LEPIDOLITE',1,9);
INSERT INTO "GoodNames" VALUES(55,'URANIUM',1,NULL);
INSERT INTO "GoodNames" VALUES(56,'BAUXITE',1,9);
INSERT INTO "GoodNames" VALUES(57,'BERTRANDITE',1,9);
INSERT INTO "GoodNames" VALUES(58,'COLTAN',1,NULL);
INSERT INTO "GoodNames" VALUES(59,'GALLITE',1,NULL);
INSERT INTO "GoodNames" VALUES(60,'INDITE',1,NULL);
INSERT INTO "GoodNames" VALUES(61,'RUTILE',1,NULL);
INSERT INTO "GoodNames" VALUES(62,'URANINITE',1,NULL);
INSERT INTO "GoodNames" VALUES(63,'ADVANCED CATALYSERS',1,NULL);
INSERT INTO "GoodNames" VALUES(64,'ANIMAL MONITORS',1,NULL);
INSERT INTO "GoodNames" VALUES(65,'AQUAPONIC SYSTEMS',1,NULL);
INSERT INTO "GoodNames" VALUES(66,'ARTIFICIAL HABITAT MODULES',1,NULL);
INSERT INTO "GoodNames" VALUES(67,'AUTO-FABRICATORS',1,NULL);
INSERT INTO "GoodNames" VALUES(68,'BIOREDUCING LICHEN',1,NULL);
INSERT INTO "GoodNames" VALUES(69,'COMPUTER COMPONENTS',1,NULL);
INSERT INTO "GoodNames" VALUES(70,'H.E. SUITS',1,NULL);
INSERT INTO "GoodNames" VALUES(71,'LAND ENRICHMENT SYSTEMS',1,NULL);
INSERT INTO "GoodNames" VALUES(72,'RESONATING SEPARATORS',1,NULL);
INSERT INTO "GoodNames" VALUES(73,'ROBOTICS',1,NULL);
INSERT INTO "GoodNames" VALUES(74,'COTTON',1,NULL);
INSERT INTO "GoodNames" VALUES(75,'LEATHER',1,NULL);
INSERT INTO "GoodNames" VALUES(76,'NATURAL FABRICS',1,NULL);
INSERT INTO "GoodNames" VALUES(77,'SYNTHETIC FABRICS',1,NULL);
INSERT INTO "GoodNames" VALUES(78,'BIOWASTE',1,11);
INSERT INTO "GoodNames" VALUES(79,'CHEMICAL WASTE',1,NULL);
INSERT INTO "GoodNames" VALUES(80,'SCRAP',1,11);
INSERT INTO "GoodNames" VALUES(81,'NON-LETHAL WPNS',1,NULL);
INSERT INTO "GoodNames" VALUES(82,'PERSONAL WEAPONS',1,NULL);
INSERT INTO "GoodNames" VALUES(83,'REACTIVE ARMOUR',1,NULL);
DROP TABLE IF EXISTS "Government";
CREATE TABLE "Government" ("id" INTEGER PRIMARY KEY  NOT NULL  UNIQUE , "name" VARCHAR NOT NULL  UNIQUE );
INSERT INTO "Government" VALUES(1,'Democracy');
INSERT INTO "Government" VALUES(2,'Communism');
INSERT INTO "Government" VALUES(3,'Anarchy');
INSERT INTO "Government" VALUES(4,'Corporate');
DROP TABLE IF EXISTS "Stations";
CREATE TABLE "Stations" ("id" INTEGER PRIMARY KEY  AUTOINCREMENT  NOT NULL  UNIQUE , "name" TEXT NOT NULL , "system_id" INTEGER NOT NULL, "government_id" INTEGER);
INSERT INTO "Stations" VALUES(1,'Worlidge terminal',4,NULL);
INSERT INTO "Stations" VALUES(2,'Fairbrain station',4,NULL);
INSERT INTO "Stations" VALUES(3,'Mcnair gateway',6,4);
INSERT INTO "Stations" VALUES(4,'Yaping enterprise','',1);
INSERT INTO "Stations" VALUES(5,'Boodt','',1);
INSERT INTO "Stations" VALUES(6,'Barsanti enterprise','',1);
INSERT INTO "Stations" VALUES(7,'Bear city','',4);
INSERT INTO "Stations" VALUES(8,'Marshall ring','',1);
INSERT INTO "Stations" VALUES(9,'Kondratyev dock',7,0);
INSERT INTO "Stations" VALUES(10,'wundt hub','',0);
INSERT INTO "Stations" VALUES(11,'Armstrong station','',0);
INSERT INTO "Stations" VALUES(12,'Gantt Terminal',8,0);
INSERT INTO "Stations" VALUES(13,'Narita Station',9,0);
INSERT INTO "Stations" VALUES(15,'Kuttner Vision',10,0);
DROP TABLE IF EXISTS "Systems";
CREATE TABLE "Systems" ("id" INTEGER PRIMARY KEY  NOT NULL ,"name" VARCHAR NOT NULL ,"economy_id" INTEGER NOT NULL  DEFAULT (null) ,"government_id" INTEGER NOT NULL  DEFAULT (null) , "Population" INTEGER);
INSERT INTO "Systems" VALUES(1,'Lave',1,1,NULL);
INSERT INTO "Systems" VALUES(2,'Diso',2,3,NULL);
INSERT INTO "Systems" VALUES(3,'Leesti',2,2,NULL);
INSERT INTO "Systems" VALUES(4,'LHS 3447',4,1,1100000000);
INSERT INTO "Systems" VALUES(5,'LTT 18486',0,0,NULL);
INSERT INTO "Systems" VALUES(6,'SUN TAKUSH',0,0,NULL);
INSERT INTO "Systems" VALUES(7,'Cupis',0,0,'');
INSERT INTO "Systems" VALUES(8,'Karogonibo',0,0,0);
INSERT INTO "Systems" VALUES(9,'Sharakha',0,0,0);
INSERT INTO "Systems" VALUES(10,'Mechtan',0,0,0);
DROP TABLE IF EXISTS "prices";
CREATE TABLE "prices" ("id" INTEGER PRIMARY KEY  NOT NULL ,"good_id" INTEGER NOT NULL ,"station_id" INTEGER NOT NULL  DEFAULT (null) ,"time" DATETIME NOT NULL ,"sale_price" FLOAT,"buy_price" FLOAT);
INSERT INTO "prices" VALUES(7,2,1,'2014-12-18 20:06',365,NULL);
INSERT INTO "prices" VALUES(8,3,1,'2014-12-18 20:17',89,94);
INSERT INTO "prices" VALUES(9,17,1,'2014-12-18 20:30',420,NULL);
INSERT INTO "prices" VALUES(10,15,1,'2014-12-18',1319,NULL);
INSERT INTO "prices" VALUES(11,18,1,'2014-12-18',153,NULL);
INSERT INTO "prices" VALUES(12,2,2,'2014-12-18',357,NULL);
INSERT INTO "prices" VALUES(13,3,2,'2014-12-18',89,94);
INSERT INTO "prices" VALUES(14,18,3,'2014-12-18',37,48);
INSERT INTO "prices" VALUES(15,15,4,'2014-12-18',1421,NULL);
INSERT INTO "prices" VALUES(16,3,4,'2014-12-18',102,107);
INSERT INTO "prices" VALUES(17,43,4,'2014-12-18',631,664);
INSERT INTO "prices" VALUES(18,56,4,'2014-12-18',75,91);
INSERT INTO "prices" VALUES(19,54,4,'2014-12-18',476,502);
INSERT INTO "prices" VALUES(20,78,4,'2014-12-18',15,20);
INSERT INTO "prices" VALUES(21,3,3,'2014-12-18',90,94);
INSERT INTO "prices" VALUES(22,18,3,'2014-12-18',37,48);
INSERT INTO "prices" VALUES(23,28,3,'2014-12-18',257,269);
INSERT INTO "prices" VALUES(24,69,3,'2014-12-18',357,374);
INSERT INTO "prices" VALUES(25,78,3,'2014-12-18',11,14);
INSERT INTO "prices" VALUES(26,80,3,'2014-12-18',27,31);
INSERT INTO "prices" VALUES(27,3,5,'2014-12-18',102,108);
INSERT INTO "prices" VALUES(28,2,4,'2014-12-18',421,NULL);
INSERT INTO "prices" VALUES(29,2,7,'2014-12-18',205,220);
INSERT INTO "prices" VALUES(30,6,4,'2014-12-18',405,NULL);
INSERT INTO "prices" VALUES(31,7,5,'2014-12-18',7360,NULL);
INSERT INTO "prices" VALUES(32,46,7,'2014-12-18',8888,8903);
INSERT INTO "prices" VALUES(34,3,2,'2014-12-29 12:26:57',91,92);
CREATE VIEW "GetPlanets" AS SELECT st.id, st.name AS station, s.name AS system, gov.name AS government, eco.name AS economy
FROM stations AS st
LEFT JOIN Systems AS s ON s.id = st.system_id
LEFT JOIN government AS gov ON gov.id = s.government_id
LEFT JOIN Economy AS eco ON eco.id = s.economy_id;
CREATE VIEW "GetSystems" AS         SELECT s.id AS id, s.name AS name, gov.name AS government, eco.name AS economy FROM Systems AS s
LEFT JOIN government AS gov ON gov.id = s.government_id
LEFT JOIN Economy AS eco ON eco.id = s.economy_id;
CREATE VIEW "GoodsInfo" AS  SELECT gn.id AS good_id, gg.name AS group_name, gn.name, UPPER(st.name), p.time, p.sale_price, p.buy_price
FROM prices AS p
LEFT JOIN GoodNames AS gn ON p.good_id=gn.id
LEFT JOIN GoodGroups AS gg ON gn.group_id = gg.id
LEFT JOIN stations AS st ON p.station_id=st.id
ORDER BY gn.name, st.name, p.time;
CREATE VIEW "GoodsInfoGrouped" AS  SELECT pr.id AS record_id, gg.name AS group_name, gn.name, UPPER(s.name) AS system, UPPER(st.name) AS station, pr.sale_price, pr.buy_price, pr.time
FROM (SELECT * FROM prices ORDER BY time ASC) AS pr
LEFT JOIN GoodNames AS gn ON pr.good_id=gn.id
LEFT JOIN GoodGroups AS gg ON gn.group_id = gg.id
LEFT JOIN stations AS st ON pr.station_id=st.id
LEFT JOIN Systems AS s ON st.system_id=s.id
GROUP BY st.name, pr.good_id
ORDER BY gg.position, gn.name, s.name, st.name, st.name, pr.time DESC;
