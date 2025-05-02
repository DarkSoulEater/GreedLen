// #include "print.hpp"
// #include "ast/ast.hpp"
// #include <iostream>

// void PrintVisitor::Visit(IntExpression* expr) {
//   std::cout << expr->value << " ";
// }

// void PrintVisitor::Visit(ArithmeticExpression* expr) {
//   expr->e1->Accept(this);
//   std::cout << expr->TypeToStr() << " ";
//   expr->e2->Accept(this);
// }

// // void PrintVisitor::Visit(AddExpression* expr) {
// //   // std::cout << "+ {\n";
// //   expr->e1->Accept(this);
// //   std::cout << "+ ";
// //   expr->e2->Accept(this);
// //   std::cout << "\n";
// //   // std::cout << "}\n";
// // }

// // void PrintVisitor::Visit(SubExpression* expr){}
// // void PrintVisitor::Visit(MulExpression* expr){}
// // void PrintVisitor::Visit(DivExpression* expr){}

// void PrintVisitor::Visit(TranslUnit* unit) {
//   for (const auto& expr : unit->exprs) {
//     expr->Accept(this);
//     std::cout << "\n";
//   }
// }