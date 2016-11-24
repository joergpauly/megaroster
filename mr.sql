CREATE TABLE "tblBranches" (
    "ID" INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
    "Name1" TEXT,
    "Name2" TEXT,
    "Name3" TEXT,
    "Adress1" TEXT,
    "Adress2" TEXT,
    "Adress3" TEXT,
    "Adress4" TEXT,
    "Adress5" TEXT,
    "Hours" TEXT
);

CREATE TABLE "tblComment" (
    "ID" INTEGER PRIMARY KEY  AUTOINCREMENT  NOT NULL ,
    "PID" INTEGER,
    "Timestamp" DATETIME,
    "Comment" TEXT
);

CREATE TABLE "tblDailyRule" (
    "ID" INTEGER PRIMARY KEY  AUTOINCREMENT  NOT NULL ,
    "Desc" VARCHAR
);

CREATE TABLE "tblDrDty" (
    "ID" INTEGER PRIMARY KEY  AUTOINCREMENT  NOT NULL ,
    "DRID" INTEGER NOT NULL ,
    "DTID" INTEGER NOT NULL
);

CREATE TABLE "tblDtTypeAliases" (
    "ID" INTEGER PRIMARY KEY  AUTOINCREMENT  NOT NULL ,
    "DTID" INTEGER NOT NULL ,
    "Alias" VARCHAR NOT NULL
);

CREATE TABLE "tblDtyAccDiff" (
    "ID" INTEGER PRIMARY KEY  NOT NULL ,
    "TypID" INTEGER,
    "Year" INTEGER,
    "Month" INTEGER,
    "PerID" INTEGER,
    "Diff" INTEGER
);

CREATE TABLE "tblDtyBase" (
    "ID" INTEGER PRIMARY KEY  AUTOINCREMENT  NOT NULL ,
    "Codeletter" CHAR,
    "Desc" VARCHAR
);

CREATE TABLE "tblDuty" (
    "ID" INTEGER PRIMARY KEY  AUTOINCREMENT  NOT NULL ,
    "PersID" INTEGER NOT NULL ,
    "TypeID" INTEGER NOT NULL ,
    "DDate" DATETIME NOT NULL ,
    "Status" BOOL ,
    "TimeFrom" DATETIME,
    "TimeTo" DATETIME,
    "TimeFrom2" DATETIME,
    "TimeTo2" DATETIME,
    "Dura" DATETIME,
    "Dura2" DATETIME
);

CREATE TABLE "tblDutyTypes" (
    "ID" INTEGER PRIMARY KEY  NOT NULL ,
    "Mark" VARCHAR NOT NULL ,
    "Decr" VARCHAR NOT NULL ,
    "TimeFrom" DATETIME NOT NULL ,
    "TimeTo" DATETIME NOT NULL ,
    "TimeElapsed" DATETIME NOT NULL ,
    "MinOffBefore" DATETIME NOT NULL ,
    "MinOffAfter" DATETIME NOT NULL , "ColorR" INTEGER NOT NULL  DEFAULT 255,
    "ColorG" INTEGER NOT NULL  DEFAULT 255,
    "ColorB" INTEGER NOT NULL  DEFAULT 255,
    "TimeFrom2" DATETIME,
    "TimeTo2" DATETIME,
    "TimeElapsed2" DATETIME,
    "BaseType" INTEGER,
    "Sequence" INTEGER
);

CREATE TABLE "tblHolidays" (
    "ID" INTEGER PRIMARY KEY  AUTOINCREMENT  NOT NULL ,
    "iDay" INTEGER,
    "iMonth" INTEGER,
    "mvbl" BOOL,
    "Descr" VARCHAR
);

CREATE TABLE "tblLogbook" (
    "ID" INTEGER PRIMARY KEY  AUTOINCREMENT  NOT NULL ,
    "PID" INTEGER,
    "DtID" INTEGER,
    "OldDTID" INTEGER,
    "NewDTID" INTEGER,
    "DDateTime" DATETIME
);

CREATE TABLE "tblLogon" (
    "ID" INTEGER PRIMARY KEY  AUTOINCREMENT  NOT NULL ,
    "PID" INTEGER NOT NULL ,
    "LogonName" VARCHAR NOT NULL
);

CREATE TABLE "tblPATypes" (
    "ID" INTEGER PRIMARY KEY  AUTOINCREMENT  NOT NULL ,
    "PAID" INTEGER NOT NULL ,
    "TypeID" INTEGER NOT NULL
);

CREATE TABLE "tblPersonal" (
    "ID" INTEGER PRIMARY KEY  NOT NULL ,
    "Name" VARCHAR NOT NULL ,
    "VName" VARCHAR NOT NULL ,
    "PNr" VARCHAR NOT NULL ,
    "GebDat" DATETIME NOT NULL ,
    "SollTag" DATETIME NOT NULL ,
    "Eintritt" DATETIME NOT NULL ,
    "Austritt" DATETIME NOT NULL ,
    "PlanEdit" BOOL,
    "Admin" BOOL,
    "BreakDate" DATETIME,
    "BDdiff" DOUBLE DEFAULT 0.0
);

CREATE TABLE "tblPrealert" (
    "ID" INTEGER PRIMARY KEY  AUTOINCREMENT  NOT NULL ,
    "DDate" DATETIME NOT NULL ,
    "PersID" INTEGER NOT NULL
);

CREATE TABLE tblkumdiff (
    "ID" INTEGER NOT NULL,
    "PID" INTEGER NOT NULL,
    "Year" INTEGER NOT NULL,
    "Month" INTEGER NOT NULL,
    "Diff" DATETIME NOT NULL
);

CREATE VIEW "viewFullDuty" AS
    select * from tblDuty,
    tblDutyTypes,
    tblPersonal
        where tblDutyTypes.ID = tblDuty.TypeID
        and tblPersonal.ID = tblDuty.PersID;
