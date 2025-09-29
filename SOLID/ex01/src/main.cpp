#include "../incl/command.hpp"
#include "../incl/ThuesdayDiscountCommand.hpp"
#include "../incl/PackageReductionDiscountCommand.hpp"


int main() {
    std::cout << "=== DISCOUNT COMMAND SYSTEM ===" << std::endl << std::endl;
    
    // Test 1: Regular command on Monday (no discounts)
    std::cout << "TEST 1: Regular Command (Monday, Total < 150)" << std::endl;
    Client client1("Alice Smith");
    Command* cmd1 = new Command(1, "Monday", client1);
    cmd1->addArticle(new Article("Laptop", 80.0));
    cmd1->addArticle(new Article("Mouse", 25.0));
    cmd1->addArticle(new Article("Keyboard", 40.0));
    cmd1->printInvoice();
    delete cmd1;
    
    // Test 2: Tuesday discount (10% off)
    std::cout << "TEST 2: Tuesday Discount Command (10% off)" << std::endl;
    Client client2("Bob Johnson");
    Command* baseCmd2 = new Command(2, "Tuesday", client2);
    baseCmd2->addArticle(new Article("Monitor", 200.0));
    baseCmd2->addArticle(new Article("Webcam", 50.0));
    
    Command* cmd2 = new TuesdayDiscountCommand(baseCmd2);
    cmd2->printInvoice();
    delete cmd2;
    delete baseCmd2;
    
    // Test 3: Package reduction (order > 150 euros, get 10 euros off)
    std::cout << "TEST 3: Package Reduction Command (10 euros off for >150)" << std::endl;
    Client client3("Charlie Brown");
    Command* baseCmd3 = new Command(3, "Wednesday", client3);
    baseCmd3->addArticle(new Article("Printer", 120.0));
    baseCmd3->addArticle(new Article("Scanner", 80.0));
    
    Command* cmd3 = new PackageReductionDiscountCommand(baseCmd3);
    cmd3->printInvoice();
    delete cmd3;
    delete baseCmd3;
    
    // Test 4: Both discounts (Tuesday + Package > 150)
    std::cout << "TEST 4: Combined Discounts (Tuesday + Package Reduction)" << std::endl;
    Client client4("Diana Prince");
    Command* baseCmd4 = new Command(4, "Tuesday", client4);
    baseCmd4->addArticle(new Article("Desktop PC", 800.0));
    baseCmd4->addArticle(new Article("RAM 16GB", 100.0));
    baseCmd4->addArticle(new Article("SSD 1TB", 120.0));
    
    // Apply package reduction first, then Tuesday discount
    Command* pkgCmd4 = new PackageReductionDiscountCommand(baseCmd4);
    Command* cmd4 = new TuesdayDiscountCommand(pkgCmd4);
    cmd4->printInvoice();
    delete cmd4;
    delete pkgCmd4;
    delete baseCmd4;
    
    // Test 5: Package reduction not applied (total < 150)
    std::cout << "TEST 5: Package Reduction NOT Applied (Total < 150)" << std::endl;
    Client client5("Eve Martinez");
    Command* baseCmd5 = new Command(5, "Friday", client5);
    baseCmd5->addArticle(new Article("USB Cable", 10.0));
    baseCmd5->addArticle(new Article("HDMI Cable", 15.0));
    baseCmd5->addArticle(new Article("Adapter", 20.0));
    
    Command* cmd5 = new PackageReductionDiscountCommand(baseCmd5);
    cmd5->printInvoice();
    delete cmd5;
    delete baseCmd5;
    
    // Test 6: Tuesday discount not applied (not Tuesday)
    std::cout << "TEST 6: Tuesday Discount NOT Applied (Not Tuesday) BUT > 150 euros" << std::endl;
    Client client6("Frank Wilson");
    Command* baseCmd6 = new Command(6, "Saturday", client6);
    baseCmd6->addArticle(new Article("Graphics Card", 500.0));
    
    Command* cmd6 = new TuesdayDiscountCommand(baseCmd6);
    Command* cmd7 = new PackageReductionDiscountCommand(cmd6);
    cmd7->printInvoice();
    delete cmd7;
    delete cmd6;
    delete baseCmd6;
    
    return 0;
}
