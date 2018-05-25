-- Gunnar Martin
-- CS340
-- Spring 2015
-- Final Project: Flight Booking DATABASE

-- General Use Queries

-- Passenger SELECT
SELECT
Passenger.PsgrID,
Passenger.FirstName,
Passenger.LastName,
Passenger.DOB
FROM Passenger;

-- Passenger INSERT
INSERT INTO Passenger(FirstName, LastName, DOB) 
VALUES ([FirstName],[LastName],[DOB]);

-- Passenger UPDATE
UPDATE Passenger SET FirstName = [FirstName], LastName = [LastName]
WHERE PsgrID = [PsgrID];

-- Upgrade SELELCT
SELECT
Upgrade.UpgradeID,
Upgrade.UpgradeName
FROM Upgrade;

-- Upgrade INSERT
INSERT INTO Upgrade(UpgradeName) VALUES ([UpgradeName]);

-- Aircraft SELECT
SELECT
Aircraft.AircraftID,
Aircraft.AcType,
Aircraft.LastService,
Aircraft.YearBuilt
FROM Aircraft;

-- Aircraft UPDATE
UPDATE Aircraft SET LastService =  [LastService] 
WHERE AircraftID = [AircraftID];

-- Flight SELECT
SELECT
Flight.FlightID,
Flight.AircraftID,
Aircraft.AcType,
Flight.FlightDate,
Flight.Origin,
Flight.Destination
FROM Flight
LEFT JOIN Aircraft
ON Flight.AircraftID = Aircraft.AircraftID
ORDER BY Flight.FlightDate ASC;

-- Flight INSERT
INSERT INTO Flight(AircraftID, FlightDate, Origin, Destination)
VALUES ([AircraftID], [FlightDate],[Origin], [Destination]);

-- Ticket SELECT
SELECT
Ticket.TicketID,
Ticket.PsgrID,
Passenger.LastName,
Passenger.FirstName,
Ticket.FlightID,
Flight.FlightDate,
Flight.Origin,
Flight.Destination,
Ticket.Price
FROM Ticket
LEFT JOIN Passenger
ON Ticket.PsgrID = Passenger.PsgrID
LEFT JOIN Flight
ON Ticket.FlightID = Flight.FlightID
ORDER BY Flight.FlightID ASC;

-- Ticket INSERT
INSERT INTO Ticket(PsgrID, FlightID, Price)
VALUES ([PsgrID],[FlightID],[Price]);

-- Ticket Upgrade SELECT
SELECT
TicketUpgrade.TicketID,
TicketUpgrade.UpgradeID,
Upgrade.UpgradeName,
Passenger.LastName,
Passenger.FirstName,
Ticket.FlightID,
Flight.FlightDate,
Flight.Origin,
Flight.Destination
FROM TicketUpgrade
LEFT JOIN Ticket
ON TicketUpgrade.TicketID = Ticket.TicketID
LEFT JOIN Upgrade
ON TicketUpgrade.UpgradeID = Upgrade.UpgradeID
LEFT JOIN Passenger
ON Ticket.PsgrID = Passenger.PsgrID
LEFT JOIN Flight
ON Ticket.FlightID = Flight.FlightID
ORDER BY TicketUpgrade.TicketID ASC;

-- Ticket Upgrade Filter
SELECT
TicketUpgrade.TicketID,
TicketUpgrade.UpgradeID,
Upgrade.UpgradeName,
Passenger.LastName,
Passenger.FirstName,
Ticket.FlightID,
Flight.FlightDate,
Flight.Origin,
Flight.Destination
FROM TicketUpgrade
LEFT JOIN Ticket
ON TicketUpgrade.TicketID = Ticket.TicketID
LEFT JOIN Upgrade
ON TicketUpgrade.UpgradeID = Upgrade.UpgradeID
LEFT JOIN Passenger
ON Ticket.PsgrID = Passenger.PsgrID
LEFT JOIN Flight
ON Ticket.FlightID = Flight.FlightID
WHERE Ticket.PsgrID = [PsgrID]
ORDER BY TicketUpgrade.TicketID ASC;

-- Ticket Upgrade INSERT
INSERT INTO TicketUpgrade(TicketID, UpgradeID) VALUES ([TicketID],[UpgradeID]);

-- Ticket Upgrade DELETE
DELETE FROM TicketUpgrade WHERE TicketID = [TicketID] AND UpgradeID = [UpgradeID];















