package com.mogoweb.remoteservicecomplex;

import com.mogoweb.remoteservicecomplex.Person;

interface IStockQuoteService
{
    String getQuote(in String ticker,in Person requester);
}
