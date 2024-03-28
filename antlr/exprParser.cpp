
// Generated from expr.g4 by ANTLR 4.13.1


#include "exprListener.h"

#include "exprParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct ExprParserStaticData final {
  ExprParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  ExprParserStaticData(const ExprParserStaticData&) = delete;
  ExprParserStaticData(ExprParserStaticData&&) = delete;
  ExprParserStaticData& operator=(const ExprParserStaticData&) = delete;
  ExprParserStaticData& operator=(ExprParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag exprParserOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
ExprParserStaticData *exprParserStaticData = nullptr;

void exprParserInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (exprParserStaticData != nullptr) {
    return;
  }
#else
  assert(exprParserStaticData == nullptr);
#endif
  auto staticData = std::make_unique<ExprParserStaticData>(
    std::vector<std::string>{
      "expr"
    },
    std::vector<std::string>{
      "", "'-'", "'*'", "'/'", "'+'", "'('", "')'"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "INT", "ID", "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,9,25,2,0,7,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,3,0,12,8,0,1,0,1,
  	0,1,0,1,0,1,0,1,0,5,0,20,8,0,10,0,12,0,23,9,0,1,0,0,1,0,1,0,0,2,1,0,2,
  	3,2,0,1,1,4,4,28,0,11,1,0,0,0,2,3,6,0,-1,0,3,4,5,1,0,0,4,12,3,0,0,6,5,
  	6,5,5,0,0,6,7,3,0,0,0,7,8,5,6,0,0,8,12,1,0,0,0,9,12,5,7,0,0,10,12,5,8,
  	0,0,11,2,1,0,0,0,11,5,1,0,0,0,11,9,1,0,0,0,11,10,1,0,0,0,12,21,1,0,0,
  	0,13,14,10,5,0,0,14,15,7,0,0,0,15,20,3,0,0,6,16,17,10,4,0,0,17,18,7,1,
  	0,0,18,20,3,0,0,5,19,13,1,0,0,0,19,16,1,0,0,0,20,23,1,0,0,0,21,19,1,0,
  	0,0,21,22,1,0,0,0,22,1,1,0,0,0,23,21,1,0,0,0,3,11,19,21
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  exprParserStaticData = staticData.release();
}

}

exprParser::exprParser(TokenStream *input) : exprParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

exprParser::exprParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  exprParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *exprParserStaticData->atn, exprParserStaticData->decisionToDFA, exprParserStaticData->sharedContextCache, options);
}

exprParser::~exprParser() {
  delete _interpreter;
}

const atn::ATN& exprParser::getATN() const {
  return *exprParserStaticData->atn;
}

std::string exprParser::getGrammarFileName() const {
  return "expr.g4";
}

const std::vector<std::string>& exprParser::getRuleNames() const {
  return exprParserStaticData->ruleNames;
}

const dfa::Vocabulary& exprParser::getVocabulary() const {
  return exprParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView exprParser::getSerializedATN() const {
  return exprParserStaticData->serializedATN;
}


//----------------- ExprContext ------------------------------------------------------------------

exprParser::ExprContext::ExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<exprParser::ExprContext *> exprParser::ExprContext::expr() {
  return getRuleContexts<exprParser::ExprContext>();
}

exprParser::ExprContext* exprParser::ExprContext::expr(size_t i) {
  return getRuleContext<exprParser::ExprContext>(i);
}

tree::TerminalNode* exprParser::ExprContext::INT() {
  return getToken(exprParser::INT, 0);
}

tree::TerminalNode* exprParser::ExprContext::ID() {
  return getToken(exprParser::ID, 0);
}


size_t exprParser::ExprContext::getRuleIndex() const {
  return exprParser::RuleExpr;
}

void exprParser::ExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExpr(this);
}

void exprParser::ExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExpr(this);
}


exprParser::ExprContext* exprParser::expr() {
   return expr(0);
}

exprParser::ExprContext* exprParser::expr(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  exprParser::ExprContext *_localctx = _tracker.createInstance<ExprContext>(_ctx, parentState);
  exprParser::ExprContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 0;
  enterRecursionRule(_localctx, 0, exprParser::RuleExpr, precedence);

    size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(11);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case exprParser::T__0: {
        setState(3);
        match(exprParser::T__0);
        setState(4);
        expr(6);
        break;
      }

      case exprParser::T__4: {
        setState(5);
        match(exprParser::T__4);
        setState(6);
        expr(0);
        setState(7);
        match(exprParser::T__5);
        break;
      }

      case exprParser::INT: {
        setState(9);
        match(exprParser::INT);
        break;
      }

      case exprParser::ID: {
        setState(10);
        match(exprParser::ID);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(21);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(19);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(13);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(14);
          _la = _input->LA(1);
          if (!(_la == exprParser::T__1

          || _la == exprParser::T__2)) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(15);
          expr(6);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(16);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(17);
          _la = _input->LA(1);
          if (!(_la == exprParser::T__0

          || _la == exprParser::T__3)) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(18);
          expr(5);
          break;
        }

        default:
          break;
        } 
      }
      setState(23);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

bool exprParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 0: return exprSempred(antlrcpp::downCast<ExprContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool exprParser::exprSempred(ExprContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 5);
    case 1: return precpred(_ctx, 4);

  default:
    break;
  }
  return true;
}

void exprParser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  exprParserInitialize();
#else
  ::antlr4::internal::call_once(exprParserOnceFlag, exprParserInitialize);
#endif
}
