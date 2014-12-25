CREATE TABLE "Economy" ("id" INTEGER PRIMARY KEY  NOT NULL  UNIQUE , "name" VARCHAR NOT NULL  UNIQUE );
CREATE TABLE "GoodGroups" ("id" INTEGER PRIMARY KEY  AUTOINCREMENT  NOT NULL  UNIQUE , "position" INTEGER NOT NULL  UNIQUE , "name" TEXT UNIQUE );
CREATE TABLE "GoodNames" ("id" INTEGER PRIMARY KEY  NOT NULL  UNIQUE , "name" TEXT NOT NULL  UNIQUE , "legal" BOOL NOT NULL , "group_id" INTEGER);
CREATE TABLE "Government" ("id" INTEGER PRIMARY KEY  NOT NULL  UNIQUE , "name" VARCHAR NOT NULL  UNIQUE );
CREATE TABLE "Stations" ("id" INTEGER PRIMARY KEY  AUTOINCREMENT  NOT NULL  UNIQUE , "name" TEXT NOT NULL , "system_id" INTEGER NOT NULL, "government_id" INTEGER);
CREATE TABLE "Systems" ("id" INTEGER PRIMARY KEY  NOT NULL ,"name" VARCHAR NOT NULL ,"economy_id" INTEGER NOT NULL  DEFAULT (null) ,"government_id" INTEGER NOT NULL  DEFAULT (null) , "Population" INTEGER);
CREATE TABLE "prices" ("id" INTEGER PRIMARY KEY  NOT NULL ,"good_id" INTEGER NOT NULL ,"station_id" INTEGER NOT NULL  DEFAULT (null) ,"time" DATETIME NOT NULL ,"sale_price" FLOAT,"buy_price" FLOAT);
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
CREATE VIEW "GoodsInfoGrouped" AS  SELECT gg.name AS group_name, gn.name, UPPER(s.name) AS system, UPPER(st.name) AS station, pr.sale_price, pr.buy_price, pr.time
FROM (SELECT * FROM prices ORDER BY time ASC) AS pr
LEFT JOIN GoodNames AS gn ON pr.good_id=gn.id
LEFT JOIN GoodGroups AS gg ON gn.group_id = gg.id
LEFT JOIN stations AS st ON pr.station_id=st.id
LEFT JOIN Systems AS s ON st.system_id=s.id
GROUP BY st.name, pr.good_id
ORDER BY gg.position, gn.name, st.name, pr.time DESC;
