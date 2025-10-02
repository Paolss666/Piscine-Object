#include "../incl/Worker.hpp"

void printSeparator(const std::string& title) {
    std::cout << "\n" << std::string(60, '=') << std::endl;
    std::cout << "  " << title << std::endl;
    std::cout << std::string(60, '=') << "\n" << std::endl;
}

void printSubSection(const std::string& subtitle) {
    std::cout << "\n--- " << subtitle << " ---" << std::endl;
}

int main() {
    printSeparator("TEST 1: COMPOSITION");
    std::cout << "Worker contains Position and Statistic as DIRECT MEMBERS" << std::endl;
    std::cout << "When Worker is destroyed, Position and Statistic are also destroyed\n" << std::endl;
    
    Position pos(10, 20, 30);
    Statistic stat(5, 100);
    Worker* worker1 = new Worker(pos, stat);
    worker1->displayWorker();

    printSeparator("TEST 2: AGGREGATION + INHERITANCE");
    std::cout << "Tool (abstract class) -> Shovel and Hammer (inherit from Tool)" << std::endl;
    std::cout << "Worker HAS-A Tool (pointer): tools exist independently\n" << std::endl;
    
    printSubSection("Creating 2 tools");
    Shovel* shovel1 = new Shovel();
    Hammer* hammer1 = new Hammer();
    
    printSubSection("Assigning tools to worker1");
    worker1->giveTool(shovel1);
    worker1->giveTool(hammer1);
    std::cout << "Worker1 now has " << worker1->getTools().size() << " tools" << std::endl;
    
    printSubSection("Testing tool usage");
    shovel1->use();
    hammer1->use();
    shovel1->use();  // 2nd use
    
    printSubSection("Creating worker2");
    Worker* worker2 = new Worker(100, 200, 300, 10, 500);
    
    printSubSection("Transferring shovel1 from worker1 to worker2");
    std::cout << "IMPORTANT: The tool is automatically REMOVED from worker1!" << std::endl;
    worker2->giveTool(shovel1);
    std::cout << "Worker1 tools: " << worker1->getTools().size() << std::endl;
    std::cout << "Worker2 tools: " << worker2->getTools().size() << std::endl;

    printSeparator("TEST 3: ASSOCIATION (Workshop-Worker)");
    std::cout << "Workshop and Worker have a BIDIRECTIONAL relationship" << std::endl;
    std::cout << "A Worker can work in MULTIPLE Workshops" << std::endl;
    std::cout << "Workshop and Worker exist independently\n" << std::endl;
    
    Workshop* metalWorkshop = new Workshop();
    Workshop* woodWorkshop = new Workshop();
    
    printSubSection("Registering workers in workshops");
    metalWorkshop->registerWorker(*worker1);
    metalWorkshop->registerWorker(*worker2);
    woodWorkshop->registerWorker(*worker1);  // worker1 in 2 workshops!
    
    std::cout << "Metal workshop: " << metalWorkshop->getWorkersCount() << " workers" << std::endl;
    std::cout << "Wood workshop: " << woodWorkshop->getWorkersCount() << " workers" << std::endl;
    
    printSubSection("Executing work");
    metalWorkshop->executeWork();
    woodWorkshop->executeWork();
    
    printSubSection("Removing worker1 from metal workshop");
    metalWorkshop->releaseWorker(*worker1);
    std::cout << "Metal workshop now has: " << metalWorkshop->getWorkersCount() << " workers" << std::endl;

    printSeparator("TEST 4: AGGREGATION - Independent Tools");
    std::cout << "Demonstrating that TOOLS survive Worker destruction\n" << std::endl;
    
    Worker* worker3 = new Worker(500, 600, 700, 15, 1000);
    
    printSubSection("Transferring hammer1 to worker3");
    std::cout << "Worker1 tools before: " << worker1->getTools().size() << std::endl;
    worker3->giveTool(hammer1);
    std::cout << "Worker1 tools after: " << worker1->getTools().size() << std::endl;
    std::cout << "Worker3 tools after: " << worker3->getTools().size() << std::endl;
    
    printSubSection("Creating more tools");
    Shovel* shovel2 = new Shovel();
    Hammer* hammer2 = new Hammer();
    worker3->giveTool(shovel2);
    worker3->giveTool(hammer2);
    
    std::cout << "\nWorker3 now has " << worker3->getTools().size() << " tools:" << std::endl;
    const std::vector<Tool*>& tools = worker3->getTools();
    for (size_t i = 0; i < tools.size(); ++i) {
        std::cout << "  Tool " << (i+1) << " - Uses: " << tools[i]->getNumberOfUses() << std::endl;
    }

    printSeparator("TEST 5: PROPER DESTRUCTION");
    
    printSubSection("Destroying workshops");
    std::cout << "Workers are automatically removed from workshops" << std::endl;
    delete metalWorkshop;
    delete woodWorkshop;
    
    printSubSection("Destroying worker3");
    std::cout << "Tools are NOT destroyed (Aggregation!)" << std::endl;
    delete worker3;
    
    printSubSection("Verifying tools still exist");
    std::cout << "Hammer1 still exists and can be used:" << std::endl;
    worker1->giveTool(hammer1);  // Reassign to worker1
    hammer1->use();
    
    printSubSection("Destroying remaining workers");
    delete worker1;
    delete worker2;
    
    printSubSection("Final destruction of tools");
    std::cout << "Now manually destroying tools (because they are independent)" << std::endl;
    delete shovel1;
    delete hammer1;
    delete shovel2;
    delete hammer2;

    printSeparator("ALL TESTS COMPLETED SUCCESSFULLY!");
    std::cout << "\nSummary of implemented relationships:" << std::endl;
    std::cout << "COMPOSITION: Worker contains Position and Statistic" << std::endl;
    std::cout << "AGGREGATION: Worker has-a Tool (independent tools)" << std::endl;
    std::cout << "INHERITANCE: Shovel/Hammer IS-A Tool" << std::endl;
    std::cout << "ASSOCIATION: Workshop-Worker (bidirectional relationship)\n" << std::endl;
    
    return 0;
}