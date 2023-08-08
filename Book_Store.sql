
CREATE TABLE Users (
    UserID INT IDENTITY(1,1) PRIMARY KEY,
	IsControler BIT DEFAULT 0 NOT NULL, 
    Username VARCHAR(50) NOT NULL,
    Password VARCHAR(50) NOT NULL 
);


INSERT INTO Users (Username, Password)
VALUES ('Author1', 'password1');

INSERT INTO Users (Username, Password)
VALUES ('Author2', 'password2');

INSERT INTO Users (IsControler, UserName, Password)
VALUES (1, 'Author3', 'password3');



CREATE TABLE Books (
	BookID INT IDENTITY(1,1) PRIMARY KEY, 
    Title VARCHAR(100) NOT NULL, 
    Author VARCHAR(100) NOT NULL,  
    Publisher VARCHAR(100) NOT NULL, 
    Pubdate VARCHAR(50) NOT NULL,  
    Price DECIMAL(10, 2) NOT NULL,
	Copies INT DEFAULT 3 NOT NULL  
);

INSERT INTO Books (Title, Author, Publisher, Pubdate, Price,Copies)VALUES
( 'a1', 'Author 1', 'Publisher 1', '2022-01-01', 19.99, 1);

INSERT INTO Books (Title, Author, Publisher, Pubdate, Price)VALUES
( 'a2', 'Author 2', 'Publisher 2', '2022-02-01', 24.99),
( 'a3', 'Author 3', 'Publisher 3', '2022-03-01', 14.99),
( 'a4', 'Author 4', 'Publisher 4', '2022-04-01', 29.99),
( 'a5', 'Author 5', 'Publisher 5', '2022-05-01', 9.99),
( 'a6', 'Author 6', 'Publisher 6', '2022-06-01', 19.99),
( 'a7', 'Author 7', 'Publisher 7', '2022-07-01', 10.6),
( 'a8', 'Author 8', 'Publisher 8', '2022-08-01', 13.99),
( 'a9', 'Author 9', 'Publisher 9', '2022-09-01', 16.99),
( 'b1', 'Author 10', 'Publisher 10', '2022-10-01', 17),
( 'b2', 'Author 11', 'Publisher 11', '2022-11-01', 11.98),
( 'b3', 'Author 12', 'Publisher 12', '2022-12-01', 7.63),
( 'b4', 'Author 13', 'Publisher 13', '2023-01-01', 9.99),
( 'b5', 'Author 14', 'Publisher 14', '2023-02-01', 15.6),
( 'b6', 'Author 15', 'Publisher 15', '2023-03-01', 14.3),
( 'b7', 'Author 16', 'Publisher 16', '2023-04-01', 16.3),
( 'b8', 'Author 17', 'Publisher 17', '2023-05-01', 23.87),
( 'b9', 'Author 18', 'Publisher 18', '2023-06-01', 42.6),
( 'c1', 'Author 19', 'Publisher 19', '2023-07-01', 39.61),
( 'c2', 'Author 20', 'Publisher 20', '2023-08-01', 39.99);

CREATE TABLE Borrow(
    BorrowingID INT IDENTITY(1,1) PRIMARY KEY,  --借阅号
    UserID INT,		--用户ID
    BookID INT,		--图书号
    BorrowDate VARCHAR(20) NOT NULL,		--借阅日期
    ReturnDate VARCHAR(20) NOT NULL　,     --还书日期
 
	Overtime BIT NOT NULL, --是否已还
    FOREIGN KEY (UserID) REFERENCES Users(UserID),
    FOREIGN KEY (BookID) REFERENCES Books(BookID)
);

INSERT INTO Borrow (UserID, BookID, BorrowDate, ReturnDate, Overtime)
VALUES (1, 1, '2022-11-01', '2023-04-01', 1);

INSERT INTO Borrow (UserID, BookID, BorrowDate, ReturnDate, Overtime)
VALUES (2, 1, '2022-04-01', '2022-06-01', 0);

drop table Users
drop table Books
drop table Borrow

select * from Users
select * from Books
select * from Borrow