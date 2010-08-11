/**
 * The FunctionX class wrapps an object method and maps it's arguments
 * from javascript.
 */

#ifndef V8_SCRIPT_FUNCTION_HPP
#define V8_SCRIPT_FUNCTION_HPP

#include "Types.h"
#include "TypeList.h"
#include "Translate.h"

namespace binding {

   template <typename O, typename R, class TList>
   class FunctionImpl;

   template <typename O, typename R>
   class FunctionImpl<O, R, NullType>
   {
      public:
         virtual R call(O *, EmptyType, EmptyType, EmptyType, EmptyType, EmptyType, EmptyType) = 0;
         virtual ~FunctionImpl() {}
   };

   template <typename O, typename R, typename P1>
   class FunctionImpl<O, R, TYPELIST_1(P1)>
   {
      public:
         virtual R call(O *, P1, EmptyType, EmptyType, EmptyType, EmptyType, EmptyType) = 0;
         virtual ~FunctionImpl() {}
   };

   template <typename O, typename R, typename P1, typename P2>
   class FunctionImpl<O, R, TYPELIST_2(P1, P2)>
   {
      public:
         virtual R call(O *, P1, P2, EmptyType, EmptyType, EmptyType, EmptyType) = 0;
         virtual ~FunctionImpl() {}
   };
   
   template <typename O, typename R, typename P1, typename P2, typename P3>
   class FunctionImpl<O, R, TYPELIST_3(P1, P2, P3)>
   {
      public:
         virtual R call(O *, P1, P2, P3, EmptyType, EmptyType, EmptyType) = 0;
         virtual ~FunctionImpl() {}
   };
   
   template <typename O, typename R, typename P1, typename P2, typename P3, typename P4>
   class FunctionImpl<O, R, TYPELIST_4(P1, P2, P3, P4)>
   {
      public:
         virtual R call(O *, P1, P2, P3, P4, EmptyType, EmptyType) = 0;
         virtual ~FunctionImpl() {}
   };
   
   template <typename O, typename R, typename P1, typename P2, typename P3, typename P4, typename P5>
   class FunctionImpl<O, R, TYPELIST_5(P1, P2, P3, P4, P5)>
   {
      public:
         virtual R call(O *, P1, P2, P3, P4, P5, EmptyType) = 0;
         virtual ~FunctionImpl() {}
   };
   
   template <typename O, typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
   class FunctionImpl<O, R, TYPELIST_6(P1, P2, P3, P4, P5, P6)>
   {
      public:
         virtual R call(O *, P1, P2, P3, P4, P5, P6) = 0;
         virtual ~FunctionImpl() {}
   };



   template <int count, class Parent, typename MethodT>
   struct Caller : public FunctionImpl<typename Parent::O, typename Parent::R, typename Parent::L>
   { };
   
   template <class Parent, typename MethodT>
   struct Caller<0, Parent, MethodT> : public FunctionImpl<typename Parent::O, typename Parent::R, typename Parent::L>
   {
      Caller(MethodT method)
         : m_method(method)
      { }
      
      typename Parent::R call(typename Parent::O * object, 
                              EmptyType p1, EmptyType p2, EmptyType p3,
                              EmptyType p4, EmptyType p5, EmptyType p6)
      {
         return ((*object).*m_method)();
      }
      
      MethodT m_method;
   };
   
   template <class Parent, typename MethodT>
   struct Caller<1, Parent, MethodT> : public FunctionImpl<typename Parent::O, typename Parent::R, typename Parent::L>
   {
      Caller(MethodT method)
         : m_method(method)
      { }
      
      typename Parent::R call(typename Parent::O * object, 
                              typename Parent::Param1 p1, EmptyType p2, EmptyType p3,
                              EmptyType p4, EmptyType p5, EmptyType p6)
      {
         return ((*object).*m_method)(p1);
      }
      
      MethodT m_method;
   };
   
   template <class Parent, typename MethodT>
   struct Caller<2, Parent, MethodT> : public FunctionImpl<typename Parent::O, typename Parent::R, typename Parent::L>
   {
      Caller(MethodT method)
         : m_method(method)
      { }
      
      typename Parent::R call(typename Parent::O * object, 
                              typename Parent::Param1 p1, typename Parent::Param2 p2, EmptyType p3,
                              EmptyType p4, EmptyType p5, EmptyType p6)
      {
         return ((*object).*m_method)(p1, p2);
      }
      
      MethodT m_method;
   };
   
   template <class Parent, typename MethodT>
   struct Caller<3, Parent, MethodT> : public FunctionImpl<typename Parent::O, typename Parent::R, typename Parent::L>
   {      
      Caller(MethodT method)
         : m_method(method)
      { }
      
      typename Parent::R call(typename Parent::O * object, 
                              typename Parent::Param1 p1, typename Parent::Param2 p2, typename Parent::Param3 p3,
                              EmptyType p4, EmptyType p5, EmptyType p6)
      {
         return ((*object).*m_method)(p1, p2, p3);
      }
      
      MethodT m_method;
   };

   template <class Parent, typename MethodT>
   struct Caller<4, Parent, MethodT> : public FunctionImpl<typename Parent::O, typename Parent::R, typename Parent::L>
   {      
      Caller(MethodT method)
         : m_method(method)
      { }
      
      typename Parent::R call(typename Parent::O * object, 
                              typename Parent::Param1 p1, typename Parent::Param2 p2, typename Parent::Param3 p3, 
                              typename Parent::Param4 p4, EmptyType p5, EmptyType p6)
      {
         return ((*object).*m_method)(p1, p2, p3, p4);
      }
      
      MethodT m_method;
   };
   
   template <class Parent, typename MethodT>
   struct Caller<5, Parent, MethodT> : public FunctionImpl<typename Parent::O, typename Parent::R, typename Parent::L>
   {      
      Caller(MethodT method)
         : m_method(method)
      { }
      
      typename Parent::R call(typename Parent::O * object, 
                              typename Parent::Param1 p1, typename Parent::Param2 p2, typename Parent::Param3 p3, 
                              typename Parent::Param4 p4, typename Parent::Param5 p5, EmptyType p6)
      {
         return ((*object).*m_method)(p1, p2, p3, p4, p5);
      }
      
      MethodT m_method;
   };
   
   template <class Parent, typename MethodT>
   struct Caller<6, Parent, MethodT> : public FunctionImpl<typename Parent::O, typename Parent::R, typename Parent::L>
   {      
      Caller(MethodT method)
         : m_method(method)
      { }
      
      typename Parent::R call(typename Parent::O * object, 
                              typename Parent::Param1 p1, typename Parent::Param2 p2, typename Parent::Param3 p3, 
                              typename Parent::Param4 p4, typename Parent::Param5 p5, typename Parent::Param6 p6)
      {
         return ((*object).*m_method)(p1, p2, p3, p4, p5);
      }
      
      MethodT m_method;
   };
   
   
   class BaseFunctor
   {
      public:
         virtual v8::Handle<v8::Value> call(v8::Arguments const& args) = 0;
   };
   
   template <typename ObjectT, typename ReturnT, class Params>
   class Functor : public BaseFunctor
   {
         enum { ArgCount = TL::Length<Params>::Value };
         
      public:
         // I know the names of these typedef's should be longer, but there is already to much code
         // in the Caller class. So readability had to take one for the team.
         typedef ReturnT R;
         typedef ObjectT O;
         typedef Params L;
         typedef typename TL::TypeAtNonStrict<Params, EmptyType, 0>::Result Param1;
         typedef typename TL::TypeAtNonStrict<Params, EmptyType, 1>::Result Param2;
         typedef typename TL::TypeAtNonStrict<Params, EmptyType, 2>::Result Param3;
         typedef typename TL::TypeAtNonStrict<Params, EmptyType, 3>::Result Param4;
         typedef typename TL::TypeAtNonStrict<Params, EmptyType, 4>::Result Param5;
         typedef typename TL::TypeAtNonStrict<Params, EmptyType, 5>::Result Param6;
               
      public:
         template <typename MethodT>
         Functor(MethodT method)
            : m_caller((FunctionImpl<ObjectT, ReturnT, Params>*)new Caller<ArgCount, Functor<ObjectT, ReturnT, Params>, MethodT>(method))
         { }
         
         virtual ~Functor()
         {
            delete m_caller;
         }
            
         v8::Handle<v8::Value> call(v8::Arguments const& args)
         {
            return Translate<ReturnT>::from(m_caller->call(Object<ObjectT>::unwrap(args.Holder()),
                                                           Translate<Param1>::to(getArg(args, 0)), 
                                                           Translate<Param2>::to(getArg(args, 1)),
                                                           Translate<Param3>::to(getArg(args, 2)),
                                                           Translate<Param4>::to(getArg(args, 3)),
                                                           Translate<Param5>::to(getArg(args, 4)),
                                                           Translate<Param6>::to(getArg(args, 5))));
         }
      
      private:
         v8::Handle<v8::Value> getArg(v8::Arguments const& args, unsigned int index)
         {
            return index < ArgCount ? args[index] : v8::Handle<v8::Value>((v8::Value*)*v8::Undefined());
         }
      
      private:
         FunctionImpl<ObjectT, ReturnT, Params> * m_caller;
   };
   
   /// Specialization of the function for methods that returns void
   template <typename ObjectT, class Params>
   class Functor<ObjectT, void, Params> : public BaseFunctor
   {
         enum { ArgCount = TL::Length<Params>::Value };
         
      public:
         // I know the names of these typedef's should be longer, but there is already to much code
         // in the Caller class. So readability had to take one for the team.
         typedef void R;
         typedef ObjectT O;
         typedef Params L;
         typedef typename TL::TypeAtNonStrict<Params, EmptyType, 0>::Result Param1;
         typedef typename TL::TypeAtNonStrict<Params, EmptyType, 1>::Result Param2;
         typedef typename TL::TypeAtNonStrict<Params, EmptyType, 2>::Result Param3;
         typedef typename TL::TypeAtNonStrict<Params, EmptyType, 3>::Result Param4;
         typedef typename TL::TypeAtNonStrict<Params, EmptyType, 4>::Result Param5;
         typedef typename TL::TypeAtNonStrict<Params, EmptyType, 5>::Result Param6;
               
      public:
         template <typename MethodT>
         Functor(MethodT method)
            : m_caller((FunctionImpl<ObjectT, void, Params>*)new Caller<ArgCount, Functor<ObjectT, void, Params>, MethodT>(method))
         { }
         
         virtual ~Functor()
         {
            delete m_caller;
         }
            
         v8::Handle<v8::Value> call(v8::Arguments const& args)
         {
            m_caller->call(Object<ObjectT>::unwrap(args.Holder()),
                           Translate<Param1>::to(getArg(args, 0)), 
                           Translate<Param2>::to(getArg(args, 1)),
                           Translate<Param3>::to(getArg(args, 2)),
                           Translate<Param4>::to(getArg(args, 3)),
                           Translate<Param5>::to(getArg(args, 4)),
                           Translate<Param6>::to(getArg(args, 5)));
                   
            return v8::Undefined();
         }
      
      private:
         v8::Handle<v8::Value> getArg(v8::Arguments const& args, unsigned int index)
         {
            return index < ArgCount ? args[index] : v8::Handle<v8::Value>((v8::Value*)*v8::Undefined());
         }
      
      private:
         FunctionImpl<ObjectT, void, Params> * m_caller;
   };
   
}

#endif

