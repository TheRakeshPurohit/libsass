// sass.hpp must go before all system headers to get the
// __EXTENSIONS__ fix on Solaris.
#include "sass.hpp"
#include "ast.hpp"


namespace Sass {

  /////////////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////////

  SupportsRule::SupportsRule(SourceSpan pstate, SupportsConditionObj condition, Block_Obj block)
  : ParentStatement(pstate, block), condition_(condition)
  { statement_type(SUPPORTS); }
  SupportsRule::SupportsRule(const SupportsRule* ptr)
  : ParentStatement(ptr), condition_(ptr->condition_)
  { statement_type(SUPPORTS); }
  bool SupportsRule::bubbles() { return true; }

  /////////////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////////

  SupportsCondition::SupportsCondition(SourceSpan pstate)
  : Expression(pstate)
  { }

  SupportsCondition::SupportsCondition(const SupportsCondition* ptr)
  : Expression(ptr)
  { }

  /////////////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////////

  Supports_Operator::Supports_Operator(SourceSpan pstate, SupportsConditionObj l, SupportsConditionObj r, Operand o)
  : SupportsCondition(pstate), left_(l), right_(r), operand_(o)
  { }
  Supports_Operator::Supports_Operator(const Supports_Operator* ptr)
  : SupportsCondition(ptr),
    left_(ptr->left_),
    right_(ptr->right_),
    operand_(ptr->operand_)
  { }

  bool Supports_Operator::needs_parens(SupportsConditionObj cond) const
  {
    if (Supports_Operator_Obj op = Cast<Supports_Operator>(cond)) {
      return op->operand() != operand();
    }
    return Cast<Supports_Negation>(cond) != NULL;
  }

  /////////////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////////

  Supports_Negation::Supports_Negation(SourceSpan pstate, SupportsConditionObj c)
  : SupportsCondition(pstate), condition_(c)
  { }
  Supports_Negation::Supports_Negation(const Supports_Negation* ptr)
  : SupportsCondition(ptr), condition_(ptr->condition_)
  { }

  bool Supports_Negation::needs_parens(SupportsConditionObj cond) const
  {
    return Cast<Supports_Negation>(cond) ||
           Cast<Supports_Operator>(cond);
  }

  /////////////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////////

  Supports_Declaration::Supports_Declaration(SourceSpan pstate, ExpressionObj f, ExpressionObj v)
  : SupportsCondition(pstate), feature_(f), value_(v)
  { }
  Supports_Declaration::Supports_Declaration(const Supports_Declaration* ptr)
  : SupportsCondition(ptr),
    feature_(ptr->feature_),
    value_(ptr->value_)
  { }

  bool Supports_Declaration::needs_parens(SupportsConditionObj cond) const
  {
    return false;
  }

  /////////////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////////

  Supports_Interpolation::Supports_Interpolation(SourceSpan pstate, ExpressionObj v)
  : SupportsCondition(pstate), value_(v)
  { }
  Supports_Interpolation::Supports_Interpolation(const Supports_Interpolation* ptr)
  : SupportsCondition(ptr),
    value_(ptr->value_)
  { }

  bool Supports_Interpolation::needs_parens(SupportsConditionObj cond) const
  {
    return false;
  }

  /////////////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////////

  IMPLEMENT_AST_OPERATORS(SupportsRule);
  IMPLEMENT_AST_OPERATORS(SupportsCondition);
  IMPLEMENT_AST_OPERATORS(Supports_Operator);
  IMPLEMENT_AST_OPERATORS(Supports_Negation);
  IMPLEMENT_AST_OPERATORS(Supports_Declaration);
  IMPLEMENT_AST_OPERATORS(Supports_Interpolation);

  /////////////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////////

}
