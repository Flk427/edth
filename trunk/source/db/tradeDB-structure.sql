CREATE TABLE "Economy" ("id" INTEGER PRIMARY KEY  NOT NULL  UNIQUE , "name" VARCHAR NOT NULL  UNIQUE );
CREATE TABLE "GoodGroups" ("id" INTEGER PRIMARY KEY  AUTOINCREMENT  NOT NULL  UNIQUE , "position" INTEGER NOT NULL  UNIQUE , "name" TEXT UNIQUE );
CREATE TABLE "GoodsNames" ("id" INTEGER PRIMARY KEY  NOT NULL  UNIQUE , "name" TEXT NOT NULL  UNIQUE , "legal" BOOL NOT NULL , "group_id" INTEGER);
CREATE TABLE "Government" ("id" INTEGER PRIMARY KEY  NOT NULL  UNIQUE , "name" VARCHAR NOT NULL  UNIQUE );
CREATE TABLE "Planets" ("id" INTEGER PRIMARY KEY  AUTOINCREMENT  NOT NULL  UNIQUE , "name" TEXT NOT NULL , "system_id" INTEGER NOT NULL, "government_id" INTEGER);
CREATE TABLE "Systems" ("id" INTEGER PRIMARY KEY  NOT NULL ,"name" VARCHAR NOT NULL ,"economy_id" INTEGER NOT NULL  DEFAULT (null) ,"government_id" INTEGER NOT NULL  DEFAULT (null) , "Population" INTEGER);
CREATE TABLE "prices" ("id" INTEGER PRIMARY KEY  NOT NULL ,"good_id" INTEGER NOT NULL ,"planet_id" INTEGER NOT NULL  DEFAULT (null) ,"time" DATETIME NOT NULL ,"sale_price" FLOAT,"buy_price" FLOAT);
CREATE VIEW "GetPlanets" AS    SELECT p.id, p.name AS planet, s.name AS system, gov.name AS government, eco.name AS economy FROM planets AS p
LEFT JOIN Systems AS s ON s.id = p.system_id
LEFT JOIN government AS gov ON gov.id = s.government_id
LEFT JOIN Economy AS eco ON eco.id = s.economy_id;
CREATE VIEW "GetPlanets-Wo" AS   SELECT p.name, s.name AS name, gov.name AS government, eco.name AS economy FROM planets AS p
LEFT JOIN Systems AS s ON s.id = p.system_id
LEFT JOIN government AS gov ON gov.id = s.government_id
LEFT JOIN Economy AS eco ON eco.id = s.economy_id
WHERE p.name LIKE "WO%";
CREATE VIEW "GetSystems" AS         SELECT s.id AS id, s.name AS name, gov.name AS government, eco.name AS economy FROM Systems AS s
LEFT JOIN government AS gov ON gov.id = s.government_id
LEFT JOIN Economy AS eco ON eco.id = s.economy_id;
CREATE VIEW "GoodsInfo" AS     SELECT gn.id AS good_id, gg.name AS group_name, gn.name, UPPER(pl.name), p.time, p.sale_price, p.buy_price FROM prices AS p
LEFT JOIN GoodsNames AS gn ON p.good_id=gn.id
LEFT JOIN GoodGroups AS gg ON gn.group_id = gg.id
LEFT JOIN planets AS pl ON p.planet_id=pl.id
ORDER BY gn.name, pl.name, p.time;
CREATE VIEW "GoodsInfo-FoodCart" AS              -- Only NEWEST prices!

 SELECT gg.name AS group_name, gn.name, UPPER(pl.name) AS planet, pr.sale_price, pr.buy_price, pr.time FROM (SELECT * FROM prices ORDER BY time ASC) AS pr
 LEFT JOIN GoodsNames AS gn ON pr.good_id=gn.id
LEFT JOIN GoodGroups AS gg ON gn.group_id = gg.id
LEFT JOIN Planets AS pl ON pr.planet_id=pl.id
LEFT JOIN Systems AS s ON pl.system_id=s.id
WHERE UPPER(gn.name) LIKE "FOOD C%"
GROUP BY pl.name, pr.good_id
ORDER BY gg.position, gn.name, pl.name, pr.time DESC

-- SELECT gn.name, UPPER(s.name), spot.name, sprt.name, p.time, p.sale_price, p.buy_price FROM (SELECT * FROM prices ORDER BY time ASC) AS p
-- LEFT JOIN GoodsNames AS gn ON p.good_id=gn.id
-- LEFT JOIN Systems AS s ON p.system_id=s.id
-- LEFT JOIN SystemPoliticTypes AS spot ON s.politic_type_id=spot.id
-- LEFT JOIN SystemProductionTypes AS sprt ON s.production_type_id=sprt.id
-- GROUP BY s.name, p.good_id
-- ORDER BY gn.name, s.name, p.time DESC

--SELECT * FROM prices AS p
--GROUP BY p.good_id
--ORDER BY time DESC
--LIMIT 1;
CREATE VIEW "GoodsInfoGrouped" AS            -- Only NEWEST prices!

 SELECT gg.name AS group_name, gn.name, UPPER(s.name) AS system, UPPER(pl.name) AS planet, pr.sale_price, pr.buy_price, pr.time FROM (SELECT * FROM prices ORDER BY time ASC) AS pr
 LEFT JOIN GoodsNames AS gn ON pr.good_id=gn.id
LEFT JOIN GoodGroups AS gg ON gn.group_id = gg.id
LEFT JOIN Planets AS pl ON pr.planet_id=pl.id
LEFT JOIN Systems AS s ON pl.system_id=s.id
GROUP BY pl.name, pr.good_id
ORDER BY gg.position, gn.name, pl.name, pr.time DESC

-- SELECT gn.name, UPPER(s.name), spot.name, sprt.name, p.time, p.sale_price, p.buy_price FROM (SELECT * FROM prices ORDER BY time ASC) AS p
-- LEFT JOIN GoodsNames AS gn ON p.good_id=gn.id
-- LEFT JOIN Systems AS s ON p.system_id=s.id
-- LEFT JOIN SystemPoliticTypes AS spot ON s.politic_type_id=spot.id
-- LEFT JOIN SystemProductionTypes AS sprt ON s.production_type_id=sprt.id
-- GROUP BY s.name, p.good_id
-- ORDER BY gn.name, s.name, p.time DESC

--SELECT * FROM prices AS p
--GROUP BY p.good_id
--ORDER BY time DESC
--LIMIT 1;
CREATE VIEW "GoodsInfoGrouped-WO" AS            -- Only NEWEST prices!

 SELECT gg.name AS group_name, gn.name, UPPER(pl.name) AS planet, pr.sale_price, pr.buy_price, pr.time FROM (SELECT * FROM prices ORDER BY time ASC) AS pr
 LEFT JOIN GoodsNames AS gn ON pr.good_id=gn.id
LEFT JOIN GoodGroups AS gg ON gn.group_id = gg.id
LEFT JOIN Planets AS pl ON pr.planet_id=pl.id
LEFT JOIN Systems AS s ON pl.system_id=s.id
WHERE pl.name LIKE "WO%"
GROUP BY pl.name, pr.good_id
ORDER BY gg.position, gn.name, pl.name, pr.time DESC

-- SELECT gn.name, UPPER(s.name), spot.name, sprt.name, p.time, p.sale_price, p.buy_price FROM (SELECT * FROM prices ORDER BY time ASC) AS p
-- LEFT JOIN GoodsNames AS gn ON p.good_id=gn.id
-- LEFT JOIN Systems AS s ON p.system_id=s.id
-- LEFT JOIN SystemPoliticTypes AS spot ON s.politic_type_id=spot.id
-- LEFT JOIN SystemProductionTypes AS sprt ON s.production_type_id=sprt.id
-- GROUP BY s.name, p.good_id
-- ORDER BY gn.name, s.name, p.time DESC

--SELECT * FROM prices AS p
--GROUP BY p.good_id
--ORDER BY time DESC
--LIMIT 1;
