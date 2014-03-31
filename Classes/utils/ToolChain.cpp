//
//  ToolChain.cpp
//  Demo
//
//  Created by zuopeng.liu on 14-3-20.
//
//

#include "ToolChain.h"


#if MOBAGE_SDK == 1
#include "./mobage/MobageAPI.h"
#endif


//#include <ScriptingCore.h>

ToolChain * ToolChain::instance_ = NULL;

ToolChain * ToolChain::getInstance()
{
    if (instance_)
    {
        return instance_;
    }
    instance_ = new ToolChain();
    return instance_;
}

////////////////////////////////////////////////////////////////////////////////////////
ToolChain::ToolChain()
{
    ///
}

////////////////////////////////////////////////////////////////////////////////////////
ToolChain::~ToolChain()
{
    
}

//
//#if MOBAGE_SDK == 1
//void ToolChain::createTransaction(jsval input, jsval onSuccess, jsval onError, jsval object)
//{
//    JSContext* ctx = ScriptingCore::getInstance()->getGlobalContext();
//    
//    std::string input_str ;
//    jsval_to_std_string(ctx, input, &input_str);
//    
//    if (! (onSuccess != JSVAL_VOID && onError != JSVAL_VOID && object != JSVAL_VOID) )
//    {
//        cocos2d::CCLog("parameters are null %s", "");
//    }
//    
//    MobageAdapter::createTransaction(input_str,
//                                     [onSuccess,object](std::string params) -> bool
//                                     {
//                                         JSContext* ctx = ScriptingCore::getInstance()->getGlobalContext();
//                                         
//                                         jsval retval;
//                                         jsval args[1];
//                                         args[0] = c_string_to_jsval( ctx, params.c_str());
//                                         
//                                         JS_CallFunctionValue(ctx, JSVAL_TO_OBJECT( object ), onSuccess , 1, args, &retval);
//                                         
//                                         return true;
//                                     },
//                                     [](std::string empty) -> bool
//                                     {
//                                         /// Nothing
//                                         return true;
//                                     },
//                                     [onError,object](std::string error) -> bool
//                                     {
//                                         JSContext* ctx = ScriptingCore::getInstance()->getGlobalContext();
//                                         
//                                         jsval retval;
//                                         jsval args[1];
//                                         args[0] = c_string_to_jsval( ctx, error.c_str());
//                                         
//                                         JS_CallFunctionValue(ctx, JSVAL_TO_OBJECT( object ), onError , 1, args, &retval);
//                                         
//                                         return true;
//                                     });
//}
//
//void ToolChain::openTransaction(jsval input, jsval onSuccess, jsval onError, jsval object)
//{
//    JSContext* ctx = ScriptingCore::getInstance()->getGlobalContext();
//    
//    std::string input_str ;
//    jsval_to_std_string(ctx, input, &input_str);
//    
//    MobageAdapter::openTransaction( input_str,
//                                   [onSuccess,object](std::string params) -> bool
//                                   {
//                                       JSContext* ctx = ScriptingCore::getInstance()->getGlobalContext();
//                                       
//                                       jsval retval;
//                                       jsval args[1];
//                                       args[0] = c_string_to_jsval( ctx, params.c_str());
//                                       
//                                       JS_CallFunctionValue(ctx, JSVAL_TO_OBJECT( object ), onSuccess , 1, args, &retval);
//                                       
//                                       return true;
//                                   },
//                                   [onError,object](std::string error) -> bool
//                                   {
//                                       JSContext* ctx = ScriptingCore::getInstance()->getGlobalContext();
//                                       
//                                       jsval retval;
//                                       jsval args[1];
//                                       args[0] = c_string_to_jsval( ctx, error.c_str());
//                                       
//                                       JS_CallFunctionValue(ctx, JSVAL_TO_OBJECT( object ), onError , 1, args, &retval);
//                                       
//                                       return true;
//                                   });
//}
//
//void ToolChain::closeTransaction(jsval input, jsval onSuccess, jsval onError, jsval object)
//{
//    JSContext* ctx = ScriptingCore::getInstance()->getGlobalContext();
//    
//    std::string input_str ;
//    jsval_to_std_string(ctx, input, &input_str);
//    
//    MobageAdapter::closeTransaction(input_str,
//                                    [onSuccess,object](std::string params) -> bool
//                                    {
//                                        JSContext* ctx = ScriptingCore::getInstance()->getGlobalContext();
//                                        
//                                        jsval retval;
//                                        jsval args[1];
//                                        args[0] = c_string_to_jsval( ctx, params.c_str());
//                                        
//                                        JS_CallFunctionValue(ctx, JSVAL_TO_OBJECT( object ), onSuccess , 1, args, &retval);
//                                        
//                                        return true;
//                                    },
//                                    [onError,object](std::string error) -> bool
//                                    {
//                                        JSContext* ctx = ScriptingCore::getInstance()->getGlobalContext();
//                                        
//                                        jsval retval;
//                                        jsval args[1];
//                                        args[0] = c_string_to_jsval( ctx, error.c_str());
//                                        
//                                        JS_CallFunctionValue(ctx, JSVAL_TO_OBJECT( object ), onError , 1, args, &retval);
//                                        
//                                        return true;
//                                    });
//}
//
//void ToolChain::getCurrentUser(/* jsval input, */ jsval onSuccess, jsval onError, jsval object)
//{
//    //    JSContext* ctx = ScriptingCore::getInstance()->getGlobalContext();
//    //
//    //    std::string input_str;
//    //    jsval_to_std_string(ctx, input, &input_str);
//    MobageAdapter::getCurrentUser([onSuccess,object](std::string user) -> bool
//                                  {
//                                      JSContext* ctx = ScriptingCore::getInstance()->getGlobalContext();
//                                      
//                                      jsval retval;
//                                      jsval args[1];
//                                      args[0] = c_string_to_jsval( ctx, user.c_str());
//                                      
//                                      JS_CallFunctionValue(ctx, JSVAL_TO_OBJECT( object ), onSuccess , 1, args, &retval);
//                                      
//                                      return true;
//                                  },
//                                  [onError,object](std::string error) -> bool
//                                  {
//                                      JSContext* ctx = ScriptingCore::getInstance()->getGlobalContext();
//                                      
//                                      jsval retval;
//                                      jsval args[1];
//                                      args[0] = c_string_to_jsval( ctx, error.c_str());
//                                      
//                                      JS_CallFunctionValue(ctx, JSVAL_TO_OBJECT( object ), onError , 1, args, &retval);
//                                      
//                                      return true;
//                                  });
//}
//
//#endif

