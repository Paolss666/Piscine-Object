#include "../incl/Worker.hpp"

int main() {
    std::cout << "\n========== TESTING MODULE 01 - RELATIONSHIPS ==========\n" << std::endl;

    // ========== COMPOSITION TEST ==========
    std::cout << "=== COMPOSITION TEST ===" << std::endl;
    Position pos(10, 20, 30);
    Statistic stat(5, 100);
    Worker worker1(pos, stat);
    worker1.displayWorker();
    std::cout << std::endl;

    // ========== AGGREGATION & INHERITANCE TEST ==========
    std::cout << "=== AGGREGATION & INHERITANCE TEST ===" << std::endl;
    
    // Create tools
    Shovel* shovel1 = new Shovel();
    Hammer* hammer1 = new Hammer();
    
    std::cout << "\n--- Initial tool status ---" << std::endl;
    // std::cout << "Shovel IsAlreadyOwn: " << shovel1->getIsAlreadyOwn() << std::endl;
    // std::cout << "Hammer IsAlreadyOwn: " << hammer1->getIsAlreadyOwn() << std::endl;
    
    // Give tools to worker1
    std::cout << "\n--- Giving tools to worker1 ---" << std::endl;
    worker1.giveTool(shovel1);
    worker1.giveTool(hammer1);
    worker1.displayWorker();
    
    std::cout << "\n--- Tool status after giving to worker1 ---" << std::endl;
    // std::cout << "Shovel IsAlreadyOwn: " << shovel1->getIsAlreadyOwn() << std::endl;
    // std::cout << "Hammer IsAlreadyOwn: " << hammer1->getIsAlreadyOwn() << std::endl;
    
    // Test tool usage
    std::cout << "\n--- Testing tool usage ---" << std::endl;
    shovel1->use();
    hammer1->use();
    
    // Create second worker
    std::cout << "\n--- Creating second worker ---" << std::endl;
    Worker worker2(100, 200, 300, 10, 500);
    
    // Try to give the same shovel to worker2 (should remove from worker1)
    std::cout << "\n--- Giving shovel1 to worker2 (should remove from worker1) ---" << std::endl;
    worker2.giveTool(shovel1);
    
    std::cout << "\n--- Worker status after transfer ---" << std::endl;
    std::cout << "Worker1 tools: " << worker1.getTools().size() << std::endl;
    std::cout << "Worker2 tools: " << worker2.getTools().size() << std::endl;
    std::cout << "Shovel current owner: " << (shovel1->getOwner() == &worker2 ? "Worker2" : "Other") << std::endl;
    
    // ========== ASSOCIATION TEST ==========
    std::cout << "\n=== ASSOCIATION TEST ===" << std::endl;
    
    // Create workshops
    Workshop* metalWorkshop = new Workshop();
    Workshop* woodWorkshop = new Workshop();
    
    // Register workers to workshops
    std::cout << "\n--- Registering workers to workshops ---" << std::endl;
    metalWorkshop->registerWorker(worker1);
    metalWorkshop->registerWorker(worker2);
    woodWorkshop->registerWorker(worker1);  // worker1 can be in multiple workshops

    std::cout << "\n--- Workshop status ---" << std::endl;
    std::cout << "Metal workshop workers: " << metalWorkshop->getWorkersCount() << std::endl;
    std::cout << "Wood workshop workers: " << woodWorkshop->getWorkersCount() << std::endl;
    
    // Execute work day
    std::cout << "\n--- Executing work day in metal workshop ---" << std::endl;
    metalWorkshop->executeWork();
    
    std::cout << "\n--- Executing work day in wood workshop ---" << std::endl;
    woodWorkshop->executeWork();
    
    // Test worker removal
    std::cout << "\n--- Removing worker1 from metal workshop ---" << std::endl;
    metalWorkshop->releaseWorker(worker1);
    std::cout << "Metal workshop workers after removal: " << metalWorkshop->getWorkersCount() << std::endl;
    
    // ========== TOOL TRANSFER TEST ==========
    std::cout << "\n=== TOOL TRANSFER TEST ===" << std::endl;
    
    // Create third worker
    Worker worker3(500, 600, 700, 15, 1000);
    
    // Give hammer to worker3 (should remove from worker1)
    std::cout << "\n--- Giving hammer1 to worker3 (should remove from worker1) ---" << std::endl;
    std::cout << "Before transfer - Worker1 tools: " << worker1.getTools().size() << std::endl;
    std::cout << "Before transfer - Worker3 tools: " << worker3.getTools().size() << std::endl;
    
    worker3.giveTool(hammer1);
    
    std::cout << "After transfer - Worker1 tools: " << worker1.getTools().size() << std::endl;
    std::cout << "After transfer - Worker3 tools: " << worker3.getTools().size() << std::endl;
    std::cout << "Hammer current owner: " << (hammer1->getOwner() == &worker3 ? "Worker3" : "Other") << std::endl;
    
    // ========== MULTIPLE TOOLS TEST ==========
    std::cout << "\n=== MULTIPLE TOOLS TEST ===" << std::endl;
    
    // Create more tools
    Shovel* shovel2 = new Shovel();
    Hammer* hammer2 = new Hammer();
    
    // Give multiple tools to worker3
    std::cout << "\n--- Giving multiple tools to worker3 ---" << std::endl;
    worker3.giveTool(shovel2);
    worker3.giveTool(hammer2);
    
    std::cout << "Worker3 tools count: " << worker3.getTools().size() << std::endl;
    worker3.displayWorker();
    
    // Test all tools
    std::cout << "\n--- Testing all tools of worker3 ---" << std::endl;
    const std::vector<Tool*>& worker3Tools = worker3.getTools();
    for (size_t i = 0; i < worker3Tools.size(); ++i) {
        std::cout << "Tool " << i << ": ";
        worker3Tools[i]->use();
        // std::cout << "IsAlreadyOwn: " << worker3Tools[i]->getIsAlreadyOwn() << std::endl;
    }
    
    // ========== CLEANUP TEST ==========
    std::cout << "\n=== CLEANUP TEST ===" << std::endl;
    std::cout << "--- Deleting workshops (should remove workers from workshops) ---" << std::endl;
    delete metalWorkshop;
    delete woodWorkshop;
    
    std::cout << "\n--- Final worker status ---" << std::endl;
    worker1.displayWorker();
    worker2.displayWorker();
    worker3.displayWorker();
    
    // Clean up tools (aggregation - tools survive worker destruction)
    std::cout << "\n--- Deleting tools ---" << std::endl;
    delete shovel1;
    delete hammer1;
    delete shovel2;
    delete hammer2;
    
    std::cout << "\n========== ALL TESTS COMPLETED ==========\n" << std::endl;
    
    return 0;
}