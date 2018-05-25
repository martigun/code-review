-- Gunnar Martin
-- CS340
-- Spring 2015
-- Final Project: Flight Booking DATABASE

-- Table Creation Queries

-- Drop these tables if they exist

DROP TABLE IF EXISTS TicketUpgrade;
DROP TABLE IF EXISTS Ticket;
DROP TABLE IF EXISTS Flight;
DROP TABLE IF EXISTS Passenger;
DROP TABLE IF EXISTS Upgrade;
DROP TABLE IF EXISTS Aircraft;

-- create passenger table
CREATE TABLE Passenger (
  PsgrID SMALLINT UNSIGNED NOT NULL AUTO_INCREMENT,
  FirstName VARCHAR(255) NOT NULL,
  LastName VARCHAR(255) NOT NULL,
  DOB DATE NOT NULL,
  PRIMARY KEY  (PsgrID)
)ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- create Upgrade table
CREATE TABLE Upgrade (
	UpgradeID SMALLINT UNSIGNED NOT NULL AUTO_INCREMENT,
	UpgradeName VARCHAR(255) NOT NULL,
	PRIMARY KEY (UpgradeID)
)ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- create Aircraft table
CREATE TABLE Aircraft (
	AircraftID SMALLINT UNSIGNED NOT NULL AUTO_INCREMENT,
	AcType VARCHAR(255) NOT NULL,
	LastService DATE NOT NULL,
	YearBuilt SMALLINT UNSIGNED NOT NULL,
	PRIMARY KEY (AircraftID)
)ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- create Flight table
CREATE TABLE Flight (
	FlightID SMALLINT UNSIGNED NOT NULL AUTO_INCREMENT,
	AircraftID SMALLINT UNSIGNED NOT NULL,
	FlightDate DATE NOT NULL,
	Origin VARCHAR(3) NOT NULL,
	Destination VARCHAR(3) NOT NULL,
	PRIMARY KEY (FlightID),
	CONSTRAINT fk_flight_aircraft FOREIGN KEY (AircraftID) REFERENCES Aircraft (AircraftID) ON DELETE RESTRICT ON UPDATE CASCADE
)ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- create Ticket table
CREATE TABLE Ticket (
	TicketID SMALLINT UNSIGNED NOT NULL AUTO_INCREMENT,
	PsgrID SMALLINT UNSIGNED NOT NULL,
	FlightID SMALLINT UNSIGNED NOT NULL,
	Price SMALLINT UNSIGNED NOT NULL,
	PRIMARY KEY (TicketID),
	CONSTRAINT fk_ticket_psgr FOREIGN KEY (PsgrID) REFERENCES Passenger (PsgrID) ON DELETE RESTRICT ON UPDATE CASCADE,
	CONSTRAINT fk_ticket_flight FOREIGN KEY (FlightID) REFERENCES Flight (FlightID) ON DELETE RESTRICT ON UPDATE CASCADE
)ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- create TicketUpdgrade table
CREATE TABLE TicketUpgrade (
	TicketID SMALLINT UNSIGNED NOT NULL,
	UpgradeID SMALLINT UNSIGNED NOT NULL,
	PRIMARY KEY (TicketID, UpgradeID),
	CONSTRAINT fk_tu_ticket FOREIGN KEY (TicketID) REFERENCES Ticket (TicketID) ON DELETE RESTRICT ON UPDATE CASCADE,
	CONSTRAINT fk_tu_upgrade FOREIGN KEY (UpgradeID) REFERENCES Upgrade(UpgradeID) ON DELETE RESTRICT ON UPDATE CASCADE
)ENGINE=InnoDB DEFAULT CHARSET=utf8;


-- The rest of the queries below are just to seed the database with some data

INSERT INTO Passenger VALUES
(NULL,'Matt','Smith','1986-02-23'),
(NULL,'Matt','Cole','1967-02-17'),
(NULL,'Matt','Kane','1968-10-19'),
(NULL,'John','Dawson','1966-04-15'),
(NULL,'Beth','Jones','1989-04-23'),
(NULL,'George','Dawson','1986-03-17'),
(NULL,'George','Glenstein','1985-02-21'),
(NULL,'George','Fink','1989-09-25'),
(NULL,'Phil','Cole','1985-08-09'),
(NULL,'Jane','Doe','1983-01-08');

INSERT INTO Upgrade VALUES
(NULL,'Free Movies'),
(NULL,'Extra Legroom'),
(NULL,'Early Boarding'),
(NULL,'Free Headphones'),
(NULL,'Free Checked Bag'),
(NULL,'Free Beverages');

INSERT INTO Aircraft VALUES
(NULL,'B737-900ER','2015-01-15',2010),
(NULL,'B737-900ER','2015-03-12',2012),
(NULL,'A320-200','2014-10-05',2005),
(NULL,'B717-200','2015-04-21',1998),
(NULL,'CRJ-900','2015-02-14',2002),
(NULL,'B737-900ER','2013-01-15',2013);


INSERT INTO Flight VALUES
(NULL,2,'2015-06-15','JFK','LGA'),
(NULL,4,'2015-06-11','JFK','LAX'),
(NULL,2,'2015-06-15','LAX','DTW'),
(NULL,3,'2015-06-12','LAX','DTW'),
(NULL,2,'2015-06-14','MCO','JFK'),
(NULL,3,'2015-06-15','SFO','DTW'),
(NULL,6,'2015-06-13','JFK','JFK'),
(NULL,3,'2015-06-10','ATL','JFK'),
(NULL,4,'2015-06-12','ORD','SFO'),
(NULL,3,'2015-06-19','ORD','DTW');

INSERT INTO Ticket VALUES
(NULL,1,10,230),
(NULL,4,1,240),
(NULL,4,4,230),
(NULL,10,1,195),
(NULL,1,7,195),
(NULL,6,7,230),
(NULL,10,8,175),
(NULL,4,3,240),
(NULL,3,5,220),
(NULL,3,3,200),
(NULL,1,8,250),
(NULL,4,2,240),
(NULL,2,5,185),
(NULL,10,2,215),
(NULL,7,5,240),
(NULL,10,9,240),
(NULL,6,7,205),
(NULL,8,10,155),
(NULL,6,4,225),
(NULL,10,6,185);

INSERT INTO TicketUpgrade VALUES
(14,6),
(9,1),
(15,4),
(6,2),
(2,5),
(6,1),
(7,6),
(10,2),
(15,6),
(6,4);







