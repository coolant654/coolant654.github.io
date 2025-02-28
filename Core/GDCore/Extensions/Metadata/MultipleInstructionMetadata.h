/*
 * GDevelop Core
 * Copyright 2008-present Florian Rival (Florian.Rival@gmail.com). All rights
 * reserved. This project is released under the MIT License.
 */
#ifndef MULTIPLEINSTRUCTIONSMETADATA_H
#define MULTIPLEINSTRUCTIONSMETADATA_H
#include "GDCore/Extensions/Metadata/ExpressionMetadata.h"
#include "GDCore/Extensions/Metadata/InstructionMetadata.h"
#include "GDCore/String.h"
namespace gd {}  // namespace gd

namespace gd {

/**
 * \brief A "composite" metadata that can be used to easily declare
 * both an expression and a related condition (and a related action)
 * without writing manually the three of them.
 *
 * \ingroup PlatformDefinition
 */
class GD_CORE_API MultipleInstructionMetadata {
 public:
  static MultipleInstructionMetadata WithExpressionAndCondition(
      gd::ExpressionMetadata &expression, gd::InstructionMetadata &condition) {
    return MultipleInstructionMetadata(expression, condition);
  }
  static MultipleInstructionMetadata WithExpressionAndConditionAndAction(
      gd::ExpressionMetadata &expression,
      gd::InstructionMetadata &condition,
      gd::InstructionMetadata &action) {
    return MultipleInstructionMetadata(expression, condition, action);
  }

  /**
   * \see gd::InstructionMetadata::AddParameter
   */
  MultipleInstructionMetadata &AddParameter(
      const gd::String &type,
      const gd::String &label,
      const gd::String &supplementaryInformation = "",
      bool parameterIsOptional = false) {
    if (expression)
      expression->AddParameter(
          type, label, supplementaryInformation, parameterIsOptional);
    if (condition)
      condition->AddParameter(
          type, label, supplementaryInformation, parameterIsOptional);
    if (action)
      action->AddParameter(
          type, label, supplementaryInformation, parameterIsOptional);
    return *this;
  }

  /**
   * \see gd::InstructionMetadata::AddCodeOnlyParameter
   */
  MultipleInstructionMetadata &AddCodeOnlyParameter(
      const gd::String &type, const gd::String &supplementaryInformation) {
    if (expression)
      expression->AddCodeOnlyParameter(type, supplementaryInformation);
    if (condition)
      condition->AddCodeOnlyParameter(type, supplementaryInformation);
    if (action) action->AddCodeOnlyParameter(type, supplementaryInformation);
    return *this;
  }

  /**
   * \see gd::InstructionMetadata::SetDefaultValue
   */
  MultipleInstructionMetadata &SetDefaultValue(const gd::String &defaultValue) {
    if (expression) expression->SetDefaultValue(defaultValue);
    if (condition) condition->SetDefaultValue(defaultValue);
    if (action) action->SetDefaultValue(defaultValue);
    return *this;
  };

  /**
   * \see gd::InstructionMetadata::SetParameterLongDescription
   */
  MultipleInstructionMetadata &SetParameterLongDescription(
      const gd::String &longDescription) {
    if (expression) expression->SetParameterLongDescription(longDescription);
    if (condition) condition->SetParameterLongDescription(longDescription);
    if (action) action->SetParameterLongDescription(longDescription);
    return *this;
  };

  /**
   * \see gd::InstructionMetadata::SetHidden
   */
  MultipleInstructionMetadata &SetHidden() {
    if (expression) expression->SetHidden();
    if (condition) condition->SetHidden();
    if (action) action->SetHidden();
    return *this;
  };

  /**
   * \see gd::InstructionMetadata::UseStandardOperatorParameters
   * \see gd::InstructionMetadata::UseStandardRelationalOperatorParameters
   */
  MultipleInstructionMetadata &UseStandardParameters(const gd::String &type) {
    if (condition) condition->UseStandardRelationalOperatorParameters(type);
    if (action) action->UseStandardOperatorParameters(type);
    return *this;
  }

  MultipleInstructionMetadata &SetFunctionName(const gd::String &functionName) {
    if (expression) expression->SetFunctionName(functionName);
    if (condition) condition->SetFunctionName(functionName);
    if (action) action->GetCodeExtraInformation().SetFunctionName(functionName);
    return *this;
  }

  MultipleInstructionMetadata &SetGetter(const gd::String &getter) {
    if (expression) expression->SetFunctionName(getter);
    if (condition) condition->SetFunctionName(getter);
    if (action) action->GetCodeExtraInformation().SetGetter(getter);
    return *this;
  }

  MultipleInstructionMetadata &SetIncludeFile(const gd::String &includeFile) {
    if (expression)
      expression->GetCodeExtraInformation().SetIncludeFile(includeFile);
    if (condition)
      condition->GetCodeExtraInformation().SetIncludeFile(includeFile);
    if (action) action->GetCodeExtraInformation().SetIncludeFile(includeFile);
    return *this;
  }

  MultipleInstructionMetadata &AddIncludeFile(const gd::String &includeFile) {
    if (expression)
      expression->GetCodeExtraInformation().AddIncludeFile(includeFile);
    if (condition)
      condition->GetCodeExtraInformation().AddIncludeFile(includeFile);
    if (action) action->GetCodeExtraInformation().AddIncludeFile(includeFile);
    return *this;
  }

  /**
   * \see gd::InstructionMetadata::MarkAsSimple
   */
  MultipleInstructionMetadata &MarkAsSimple() {
    if (condition) condition->MarkAsSimple();
    if (action) action->MarkAsSimple();
    return *this;
  }

  /**
   * \see gd::InstructionMetadata::MarkAsAdvanced
   */
  MultipleInstructionMetadata &MarkAsAdvanced() {
    if (condition) condition->MarkAsAdvanced();
    if (action) action->MarkAsAdvanced();
    return *this;
  }

  /**
   * \see gd::InstructionMetadata::MarkAsComplex
   */
  MultipleInstructionMetadata &MarkAsComplex() {
    if (condition) condition->MarkAsComplex();
    if (action) action->MarkAsComplex();
    return *this;
  }

  /**
   * \brief Don't use, only here to fulfill Emscripten bindings requirements.
   */
  MultipleInstructionMetadata()
      : expression(nullptr), condition(nullptr), action(nullptr){};

 private:
  MultipleInstructionMetadata(gd::ExpressionMetadata &expression_,
                              gd::InstructionMetadata &condition_)
      : expression(&expression_), condition(&condition_), action(nullptr){};
  MultipleInstructionMetadata(gd::ExpressionMetadata &expression_,
                              gd::InstructionMetadata &condition_,
                              gd::InstructionMetadata &action_)
      : expression(&expression_), condition(&condition_), action(&action_){};

  gd::ExpressionMetadata *expression;
  gd::InstructionMetadata *condition;
  gd::InstructionMetadata *action;
};

}  // namespace gd

#endif  // MULTIPLEINSTRUCTIONSMETADATA_H
