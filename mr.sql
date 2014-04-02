CREATE TABLE "tblDuty" ("ID" INTEGER PRIMARY KEY  AUTOINCREMENT  NOT NULL , "PersID" INTEGER NOT NULL , "TypeID" INTEGER NOT NULL , "DDate" DATETIME NOT NULL , "Status" INTEGER NOT NULL );
CREATE TABLE "tblDutyTypes" ("ID" INTEGER PRIMARY KEY  NOT NULL ,"Mark" VARCHAR NOT NULL ,"Decr" VARCHAR NOT NULL ,"TimeFrom" DATETIME NOT NULL ,"TimeTo" DATETIME NOT NULL ,"TimeElapsed" DATETIME NOT NULL ,"MinOffBefore" DATETIME NOT NULL ,"MinOffAfter" DATETIME NOT NULL , "ColorR" INTEGER NOT NULL  DEFAULT 255, "ColorG" INTEGER NOT NULL  DEFAULT 255, "ColorB" INTEGER NOT NULL  DEFAULT 255, "TimeFrom2" DATETIME, "TimeTo2" DATETIME, "TimeElapsed2" DATETIME);
CREATE TABLE "tblPersonal" ("ID" INTEGER PRIMARY KEY  AUTOINCREMENT  NOT NULL , "Name" VARCHAR NOT NULL , "VName" VARCHAR NOT NULL , "PNr" VARCHAR NOT NULL , "GebDat" DATETIME NOT NULL , "SollTag" DATETIME NOT NULL , "Eintritt" DATETIME NOT NULL , "Austritt" DATETIME NOT NULL );
