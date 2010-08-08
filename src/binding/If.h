
#ifndef V8_SCRIPT_IF_HPP
#define V8_SCRIPT_IF_HPP

namespace binding {

   template <bool Condition, typename TrueT, typename FalseT>
   struct If;
   
   template <typename TrueT, typename FalseT>
   struct If<false, TrueT, FalseT>
   {
      typedef FalseT Result;
   };
   
   template <typename TrueT, typename FalseT>
   struct If<true, TrueT, FalseT>
   {
      typedef TrueT Result;
   };

}

#endif

