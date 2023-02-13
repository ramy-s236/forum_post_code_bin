
/*
 * CGtkmmFrontEnd.cpp
 *
 *  Created on: Nov 10, 2018
 *      Author: ramy
 */

#include "sample_window.h"

#include <iostream>


sample_window::sample_window()
{
   set_type_hint(Gdk::WINDOW_TYPE_HINT_NORMAL);
//   add(m_oScrolledWindow);
   //set_default_size(800, 500);
   resize(500, 500);
   add(m_v_box);

   m_v_box.set_orientation(Gtk::ORIENTATION_VERTICAL);
   m_v_box.pack_start(m_h_box, true,  false);

   m_h_box.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
   m_h_box.pack_start(m_source_event_box, true,  false);
   m_h_box.pack_start(m_popover_trigger_event_box, true,  false);

   m_source_event_box.add(m_source_frame);
   m_source_frame.add(m_source_label);
   m_source_label.set_text("source");

   std::vector<Gtk::TargetEntry> drag_targets;
   drag_targets.push_back( Gtk::TargetEntry("STRING"));
   drag_targets.push_back( Gtk::TargetEntry("text/plain"));

   m_popover.signal_closed().connect(sigc::mem_fun(*this, &sample_window::popover_closed));
   m_popover.add(m_destination_event_box);
   m_popover.set_relative_to(m_popover_trigger_event_box);
   m_popover.set_position(Gtk::POS_BOTTOM);

   m_popover_trigger_event_box.drag_dest_set(drag_targets);
   m_popover_trigger_event_box.signal_drag_motion ().connect(sigc::mem_fun(*this, &sample_window::popover_trigger_motion_event));
   m_popover_trigger_event_box.add(m_popover_trigger_frame);
   m_popover_trigger_frame.add(m_popover_trigger_label);
   m_popover_trigger_label.set_text("trigger popover");

   m_destination_event_box.add(m_destination_frame);
   m_destination_frame.add(m_destination_label);
   m_destination_label.set_text("destination");

   m_source_event_box.drag_source_set(drag_targets);
   m_source_event_box.signal_drag_data_get().connect(sigc::mem_fun(*this, &sample_window::drag_source_data_get));

   m_destination_event_box.drag_dest_set(drag_targets);
   m_destination_event_box.signal_drag_data_received().connect(sigc::mem_fun(*this, &sample_window::drag_destination_data_received));

   show_all();
}

sample_window::~sample_window()
{
}

bool sample_window::popover_trigger_motion_event(
                const Glib::RefPtr<Gdk::DragContext>& context,
                int x,
                int y,
                guint time)
{
   if (!m_popover_is_open)
   {
      m_popover.popup();
      m_popover.show_all();
      m_popover_is_open = true;
   }

   return true;
}

void sample_window::popover_closed()
{
   m_popover_is_open = false;
}

void sample_window::drag_source_data_get(
                       const Glib::RefPtr<Gdk::DragContext>& context,
                       Gtk::SelectionData& selection_data,
                       guint info,
                       guint time)
{
   std::string source_message = "source says hello";
   selection_data.set(
         selection_data.get_target(),
         8,
         (const guchar*)source_message.c_str(),
         source_message.size());
}

void sample_window::drag_destination_data_received(
                      const Glib::RefPtr<Gdk::DragContext>& context,
                      int x,
                      int y,
                      const Gtk::SelectionData& selection_data,
                      guint info,
                      guint time)
{
   if ((selection_data.get_length() >= 0) &&
       (selection_data.get_format() == 8))
   {
      std::cout << selection_data.get_data_as_string() << std::endl;
   }

   context->drag_finish(false, false, time);
}

