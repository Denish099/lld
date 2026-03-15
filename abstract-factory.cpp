#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;


class PaymentGateway {
public:
    virtual void processPayment(double amount) = 0;
    virtual ~PaymentGateway() {}
};


class RazorPay : public PaymentGateway{
public:
    void processPayment(double amount) override{
        cout << "Processing payment via RazorPay: " << amount << endl;
    }
};

class PayUGateway: public PaymentGateway{
public:
    void processPayment(double amount) override{
        cout << "Processing payment via PayU: " << amount << endl;
    }
};


class Stripe : public PaymentGateway{
public:
    void processPayment(double amount) override{
        cout << "Processing payment via Stripe: " << amount << endl;
    }
};

class PayPal : public PaymentGateway{
public:
    void processPayment(double amount) override{
        cout << "Processing payment via PayPal: " << amount << endl;
    }
};


class Invoice{
public:
    virtual void generateInvoice() = 0;
    virtual ~Invoice() {}
};


class GSTInvoice : public Invoice{
public:
    void generateInvoice() override{
        cout << "Generating GST invoice for India" << endl;
    }
};


class USInvoice : public Invoice{
public:
    void generateInvoice() override{
        cout << "Generating US invoice" << endl;
    }
};


class PaymentFactory{
public:
    virtual PaymentGateway* createPaymentGateway(string gatewayType) = 0;
    virtual Invoice* createInvoice() = 0;
    virtual ~PaymentFactory() {}
};


class IndiaFactory : public PaymentFactory{
public:

    PaymentGateway* createPaymentGateway(string gatewayType) override{

        transform(gatewayType.begin(), gatewayType.end(),
                  gatewayType.begin(), ::tolower);

        if(gatewayType == "razorpay")
            return new RazorPay();

        if(gatewayType == "payu")
            return new PayUGateway();

        return nullptr;
    }

    Invoice* createInvoice() override{
        return new GSTInvoice();
    }
};


class USFactory : public PaymentFactory{
public:

    PaymentGateway* createPaymentGateway(string gatewayType) override{

        transform(gatewayType.begin(), gatewayType.end(),
                  gatewayType.begin(), ::tolower);

        if(gatewayType == "stripe")
            return new Stripe();

        if(gatewayType == "paypal")
            return new PayPal();

        return nullptr;
    }

    Invoice* createInvoice() override{
        return new USInvoice();
    }
};


class CheckoutService{
private:
    PaymentFactory* factory;
    string gatewayType;

public:

    CheckoutService(PaymentFactory* factory, string gatewayType){
        this->factory = factory;
        this->gatewayType = gatewayType;
    }

    void checkout(double amount){

        PaymentGateway* gateway =
            factory->createPaymentGateway(gatewayType);

        Invoice* invoice =
            factory->createInvoice();

        if(gateway){
            gateway->processPayment(amount);
        }
        else{
            cout << "Invalid payment gateway" << endl;
            return;
        }

        invoice->generateInvoice();

        delete gateway;
        delete invoice;
    }
};


int main(){

    PaymentFactory* factory = new USFactory();

    CheckoutService service(factory, "stripe");

    service.checkout(500);

    delete factory;

    return 0;
}