/*
 * CGtkmmFrontEnd.h
 *
 *  Created on: Nov 10, 2018
 *      Author: ramy
 */

#ifndef SOURCE_SAMPLE_WINDOW_H_
#define SOURCE_SAMPLE_WINDOW_H_

#include <gtkmm.h>

class sample_window: public Gtk::Window
{
public:
   sample_window();
   virtual ~sample_window();

   bool popover_trigger_motion_event(
                   const Glib::RefPtr<Gdk::DragContext>& context,
                   int x,
                   int y,
                   guint time);
   void popover_closed();

   void drag_source_data_get(
                          const Glib::RefPtr<Gdk::DragContext>& context,
                          Gtk::SelectionData& selection_data,
                          guint info,
                          guint time);

   void drag_destination_data_received(
                         const Glib::RefPtr<Gdk::DragContext>& context,
                         int x,
                         int y,
                         const Gtk::SelectionData& selection_data,
                         guint info,
                         guint time);
private:
   Gtk::Box m_h_box;
   Gtk::Box m_v_box;

   Gtk::EventBox m_source_event_box;
   Gtk::Frame m_source_frame;
   Gtk::Label m_source_label;

   Gtk::EventBox m_destination_event_box;
   Gtk::Frame m_destination_frame;
   Gtk::Label m_destination_label;
   bool m_popover_is_open = false;

   Gtk::Popover m_popover;
   Gtk::EventBox m_popover_trigger_event_box;
   Gtk::Frame m_popover_trigger_frame;
   Gtk::Label m_popover_trigger_label;
};

#endif /* SOURCE_CGTKMMFRONTEND_H_ */
