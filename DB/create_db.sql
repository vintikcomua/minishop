--
-- File generated with SQLiteStudio v3.2.1 on пт серп. 7 11:55:12 2020
--
-- Text encoding used: UTF-8
--
-- PRAGMA foreign_keys = off;
-- BEGIN TRANSACTION;

-- Table: dicClassUnits
CREATE TABLE dicClassUnits (
    id       INTEGER       PRIMARY KEY
                           NOT NULL,
    short    VARCHAR (50)  UNIQUE
                           NOT NULL,
    fullname VARCHAR (255) 
);

INSERT INTO dicClassUnits (
                              id,
                              short,
                              fullname
                          )
                          VALUES (
                              101,
                              'м',
                              'Метр'
                          );

INSERT INTO dicClassUnits (
                              id,
                              short,
                              fullname
                          )
                          VALUES (
                              171,
                              'міс',
                              'Місяць'
                          );

INSERT INTO dicClassUnits (
                              id,
                              short,
                              fullname
                          )
                          VALUES (
                              175,
                              'год',
                              'Година'
                          );

INSERT INTO dicClassUnits (
                              id,
                              short,
                              fullname
                          )
                          VALUES (
                              301,
                              'кг',
                              'Кілограм'
                          );

INSERT INTO dicClassUnits (
                              id,
                              short,
                              fullname
                          )
                          VALUES (
                              2009,
                              'шт',
                              'Штука'
                          );


-- Table: dicContragents
CREATE TABLE dicContragents (
    id           INTEGER       PRIMARY KEY AUTOINCREMENT
                               NOT NULL,
    short        VARCHAR (100) NOT NULL
                               UNIQUE,
    fullname     VARCHAR (255) NOT NULL,
    buyer        BOOLEAN       DEFAULT (true) 
                               NOT NULL,
    supplier     BOOLEAN       NOT NULL
                               DEFAULT (false),
    pricetype_id INTEGER       REFERENCES dicPriceTypes (id) ON DELETE RESTRICT
                                                             ON UPDATE CASCADE,
    phone        VARCHAR,
    email        VARCHAR
);


-- Table: dicManufacturers
CREATE TABLE dicManufacturers (
    id    INTEGER      PRIMARY KEY AUTOINCREMENT
                       NOT NULL,
    short VARCHAR (50) UNIQUE
                       NOT NULL
);


-- Table: dicPriceTypes
CREATE TABLE dicPriceTypes (
    id          INTEGER      PRIMARY KEY AUTOINCREMENT
                             NOT NULL,
    short       VARCHAR (50) NOT NULL
                             UNIQUE,
    currency_id INTEGER      REFERENCES dicСurrency (id) ON DELETE RESTRICT
                                                         ON UPDATE CASCADE
);


-- Table: dicProducts
CREATE TABLE dicProducts (
    id              INTEGER       NOT NULL
                                  PRIMARY KEY AUTOINCREMENT,
    short           VARCHAR (100) UNIQUE
                                  NOT NULL,
    article         VARCHAR (50)  NOT NULL
                                  DEFAULT (''),
    unit_id         INTEGER       REFERENCES dicClassUnits (id) ON DELETE RESTRICT
                                                                ON UPDATE CASCADE
                                  NOT NULL,
    manufacturer_id INTEGER       REFERENCES dicManufacturers (id) ON DELETE RESTRICT
                                                                   ON UPDATE CASCADE
);


-- Table: dicСurrency
CREATE TABLE dicСurrency (
    id       INTEGER      NOT NULL
                          PRIMARY KEY,
    short    VARCHAR (10) NOT NULL
                          UNIQUE,
    fullname VARCHAR (50) 
);

INSERT INTO dicСurrency (
                            id,
                            short,
                            fullname
                        )
                        VALUES (
                            840,
                            'USD',
                            'Долар США'
                        );

INSERT INTO dicСurrency (
                            id,
                            short,
                            fullname
                        )
                        VALUES (
                            978,
                            'EUR',
                            'євро'
                        );

INSERT INTO dicСurrency (
                            id,
                            short,
                            fullname
                        )
                        VALUES (
                            980,
                            'UAH',
                            'гривня'
                        );


-- Table: riCurrencyRates
CREATE TABLE riCurrencyRates (
    period       DATE    NOT NULL,
    currency_id  INTEGER REFERENCES dicСurrency (id) ON DELETE RESTRICT
                                                     ON UPDATE CASCADE
                         NOT NULL,
    rate         NUMERIC NOT NULL
                         DEFAULT (1),
    multiplicity NUMERIC NOT NULL
                         DEFAULT (1),
    CONSTRAINT riCurrencyRates_PK PRIMARY KEY (
        period,
        currency_id
    )
);

INSERT INTO riCurrencyRates (
                                period,
                                currency_id,
                                rate,
                                multiplicity
                            )
                            VALUES (
                                '1980-01-01',
                                980,
                                1,
                                1
                            );

INSERT INTO riCurrencyRates (
                                period,
                                currency_id,
                                rate,
                                multiplicity
                            )
                            VALUES (
                                '2020-08-07',
                                840,
                                27.6793,
                                1
                            );

INSERT INTO riCurrencyRates (
                                period,
                                currency_id,
                                rate,
                                multiplicity
                            )
                            VALUES (
                                '2020-08-07',
                                978,
                                32.7972,
                                1
                            );

INSERT INTO riCurrencyRates (
                                period,
                                currency_id,
                                rate,
                                multiplicity
                            )
                            VALUES (
                                '2020-08-01',
                                840,
                                2769.13,
                                100
                            );

INSERT INTO riCurrencyRates (
                                period,
                                currency_id,
                                rate,
                                multiplicity
                            )
                            VALUES (
                                '2020-08-01',
                                978,
                                3254.7,
                                100
                            );


-- Table: riProductAnalogs
CREATE TABLE riProductAnalogs (
    product_id INTEGER REFERENCES dicProducts (id) ON DELETE CASCADE
                                                   ON UPDATE CASCADE
                       NOT NULL,
    analog_id  INTEGER REFERENCES dicProducts (id) ON DELETE CASCADE
                                                   ON UPDATE CASCADE
                       NOT NULL,
    CONSTRAINT riProductAnalogs_PK PRIMARY KEY (
        product_id,
        analog_id
    )
);


-- Table: riProductPrices
CREATE TABLE riProductPrices (
    period       DATE    NOT NULL,
    product_id   INTEGER REFERENCES dicProducts (id) ON DELETE RESTRICT
                                                     ON UPDATE CASCADE,
    pricetype_id INTEGER REFERENCES dicPriceTypes (id) ON DELETE RESTRICT
                                                       ON UPDATE CASCADE,
    price        NUMERIC NOT NULL,
    CONSTRAINT riProductPrices_PK PRIMARY KEY (
        period,
        product_id,
        pricetype_id
    )
);


-- Table: riSearchArticles
CREATE TABLE riSearchArticles (
    product_id INTEGER      NOT NULL
                            REFERENCES dicProducts (id) ON DELETE CASCADE
                                                        ON UPDATE CASCADE,
    sarticle   VARCHAR (50) NOT NULL,
    CONSTRAINT riSearchArticle_PK PRIMARY KEY (
        product_id,
        sarticle
    )
);


-- View: riCurrencyRatesLast
CREATE VIEW riCurrencyRatesLast AS
    SELECT LastT.*
      FROM riCurrencyRates AS LastT
           INNER JOIN
           (
               SELECT MAX(Last.Period) AS Period,
                      Last.currency_id AS Id
                 FROM riCurrencyRates AS Last
                GROUP BY Last.currency_id
           )
           AS LastD ON LastT.currency_id = LastD.Id AND 
                       LastT.Period = LastD.Period;


-- View: riProductPricesLast
CREATE VIEW riProductPricesLast AS
    SELECT LastT.*
      FROM riProductPrices AS LastT
           INNER JOIN
           (
               SELECT MAX(Last.Period) AS Period,
                      Last.product_id AS Id
                 FROM riProductPrices AS Last
                GROUP BY Last.product_id
           )
           AS LastD ON LastT.product_id = LastD.Id AND 
                       LastT.Period = LastD.Period;


-- COMMIT TRANSACTION;
-- PRAGMA foreign_keys = on;
